import argparse
import os
import pickle
import matplotlib.pyplot as plt
from ann import initialize_weights, forward_pass, backward_pass
from utils import load_dataset
import numpy as np
from sklearn.model_selection import train_test_split

def train(X_train, y_train, X_val, y_val, params, lr, epochs, patience=5, delta=0.001):
    train_losses, val_losses = [], []
    train_accuracies, val_accuracies = [], []

    best_loss = np.inf
    best_params = {k: v.copy() for k, v in params.items()}
    no_improve = 0

    for epoch in range(epochs):
        out_train, cache_train = forward_pass(X_train, params)
        train_loss = -np.sum(y_train * np.log(out_train + 1e-9)) / y_train.shape[0]
        train_preds = np.argmax(out_train, axis=1)
        train_acc = np.mean(train_preds == np.argmax(y_train, axis=1))

        backward_pass(params, cache_train, y_train, lr)

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
    args = parser.parse_args()

    X_full, y_full, label_map = load_dataset("dataset/train")
    y_labels = np.argmax(y_full, axis=1)

    X_train, X_val, y_train, y_val = train_test_split(
        X_full, y_full,
        test_size=args.val_ratio,
        stratify=y_labels,
        random_state=42
    )

    input_size = X_train.shape[1]
    output_size = y_train.shape[1]
    params = initialize_weights(input_size, 128, 64, output_size)

    params = train(
        X_train, y_train, X_val, y_val,
        params, args.lr, args.epoch,
        patience=args.patience, delta=args.delta
    )

    with open("model.pkl", "wb") as f:
        pickle.dump((params, label_map), f)

