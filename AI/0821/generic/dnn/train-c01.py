import argparse
import os
import pickle
import matplotlib.pyplot as plt
from dnn import initialize_weights, forward_pass, backward_pass
from utils import load_dataset
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.utils.class_weight import compute_class_weight

def train(X_train, y_train, X_val, y_val, params, lr, epochs, patience=5, delta=0.001, class_weights=None, batch_size=64):
    train_losses, val_losses = [], []
    train_accuracies, val_accuracies = [], []

    best_loss = np.inf
    best_params = {k: v.copy() for k, v in params.items()}
    no_improve = 0

    if class_weights is not None:
        sample_weights = np.array([class_weights[cls] for cls in np.argmax(y_train, axis=1)])

    for epoch in range(epochs):
        indices = np.random.permutation(X_train.shape[0])
        X_shuffled = X_train[indices]
        y_shuffled = y_train[indices]
        if class_weights is not None:
            sw_shuffled = sample_weights[indices]
        else:
            sw_shuffled = None

        # 배치로 나누기
        n_batches = X_train.shape[0] // batch_size
        if X_train.shape[0] % batch_size != 0:
            n_batches += 1

        epoch_train_loss = 0.0
        epoch_train_acc = 0.0

        for i in range(n_batches):
            start = i * batch_size
            end = min((i+1)*batch_size, X_train.shape[0])
            X_batch = X_shuffled[start:end]
            y_batch = y_shuffled[start:end]
            if sw_shuffled is not None:
                sw_batch = sw_shuffled[start:end]
            else:
                sw_batch = None

            # Forward pass
            out_batch, cache_batch = forward_pass(X_batch, params)

            if class_weights is not None:
                loss_per_sample = -np.sum(y_batch * np.log(out_batch + 1e-9), axis=1)
                batch_loss = np.sum(loss_per_sample * sw_batch) / X_batch.shape[0]
            else:
                batch_loss = -np.sum(y_batch * np.log(out_batch + 1e-9)) / X_batch.shape[0]

            batch_preds = np.argmax(out_batch, axis=1)
            batch_acc = np.mean(batch_preds == np.argmax(y_batch, axis=1))

            if class_weights is not None:
                backward_pass(params, cache_batch, y_batch, lr, sw_batch)
            else:
                backward_pass(params, cache_batch, y_batch, lr)

            epoch_train_loss += batch_loss * X_batch.shape[0]
            epoch_train_acc += batch_acc * X_batch.shape[0]

        train_loss = epoch_train_loss / X_train.shape[0]
        train_acc = epoch_train_acc / X_train.shape[0]

        out_val, _ = forward_pass(X_val, params)
        val_loss = -np.sum(y_val * np.log(out_val + 1e-9)) / y_val.shape[0]
        val_preds = np.argmax(out_val, axis=1)
        val_acc = np.mean(val_preds == np.argmax(y_val, axis=1))

        if val_loss < best_loss - delta:
            best_loss = val_loss
            best_params = {k: v.copy() for k, v in params.items()}
            no_improve = 0
            print(f"★ Validation improved to {val_loss:.4f}")
        else:
            no_improve += 1

        train_losses.append(train_loss)
        train_accuracies.append(train_acc)
        val_losses.append(val_loss)
        val_accuracies.append(val_acc)

        print(f"Epoch {epoch+1}/{epochs} | "
              f"Train Loss: {train_loss:.4f} Acc: {train_acc:.4f} | "
              f"Val Loss: {val_loss:.4f} Acc: {val_acc:.4f} | "
              f"No improve: {no_improve}/{patience}")

        if no_improve >= patience:
            print(f"\nEarly stopping triggered at epoch {epoch+1}!")
            params = {k: v.copy() for k, v in best_params.items()}
            break

    plt.figure(figsize=(12, 5))

    plt.subplot(1, 2, 1)
    plt.plot(train_losses, label='Train Loss', marker='o', color='orange')
    plt.plot(val_losses, label='Val Loss', marker='x', color='green')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()
    plt.grid(True)
    plt.title('Training vs Validation Loss')

    plt.subplot(1, 2, 2)
    plt.plot(train_accuracies, label='Train Acc', marker='o', color='orange')
    plt.plot(val_accuracies, label='Val Acc', marker='x', color='green')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.legend()
    plt.grid(True)
    plt.title('Training vs Validation Accuracy')

    plt.tight_layout()
    plt.savefig('training_metrics.png')
    plt.show()
    plt.close()

    return params

if __name__ == '__main__':
    np.random.seed(42)

    parser = argparse.ArgumentParser()
    parser.add_argument('--epoch', type=int, default=50)
    parser.add_argument('--lr', type=float, default=0.01)
    parser.add_argument('--val_ratio', type=float, default=0.2)
    parser.add_argument('--patience', type=int, default=5, help='Number of epochs to wait before early stop')
    parser.add_argument('--delta', type=float, default=0.001, help='Minimum change to qualify as improvement')
    parser.add_argument('--use_class_weight', action='store_true', help='Use class weight for imbalanced dataset')
    parser.add_argument('--batch_size', type=int, default=64, help='Use batch_size')
    args = parser.parse_args()

    X_full, y_full, label_map = load_dataset("dataset/train")
    y_labels = np.argmax(y_full, axis=1)

    X_train, X_val, y_train, y_val = train_test_split(
        X_full, y_full,
        test_size=args.val_ratio,
        stratify=y_labels,
        random_state=42
    )

    class_weights = None
    if args.use_class_weight:
        weights = compute_class_weight(class_weight='balanced', classes=np.unique(y_labels), y=y_labels)
        class_weights = {cls: w for cls, w in zip(np.unique(y_labels), weights)}
        print(f"\nClass Weights: {class_weights}\n")

    input_size = X_train.shape[1]
    output_size = y_train.shape[1]
    params = initialize_weights(input_size, 512, 256, 128, output_size)

    params = train(
        X_train, y_train, X_val, y_val,
        params, args.lr, args.epoch,
        patience=args.patience, delta=args.delta,
        class_weights=class_weights,
        batch_size=args.batch_size
    )

    with open("model.pkl", "wb") as f:
        pickle.dump((params, label_map), f)

    # 결과 저장 루틴 추가
    # 최종 검증 정확도와 손실 계산
    out_val, _ = forward_pass(X_val, params)
    val_loss = -np.sum(y_val * np.log(out_val + 1e-9)) / y_val.shape[0]
    val_preds = np.argmax(out_val, axis=1)
    val_acc = np.mean(val_preds == np.argmax(y_val, axis=1))

    # 결과 파일명에 하이퍼파라미터 반영
    # 결과를 한 줄로 만들어 저장 (CSV 형식 추천)
    result_line = f"{args.lr},{args.batch_size},{val_loss:.6f},{val_acc:.6f}\n"
    with open("all_dnn_results.txt", "a") as rf:
        rf.write(result_line)
