import argparse
import os
import pickle
import matplotlib.pyplot as plt
from ann import initialize_weights, forward_pass, backward_pass
from utils import load_dataset
import numpy as np
import sys

def train(X_train, y_train, params, lr, epochs):
    losses, accuracies = [], []
    for epoch in range(epochs):
        out, cache = forward_pass(X_train, params)
        loss = -np.sum(y_train * np.log(out + 1e-9)) / y_train.shape[0]
        preds = np.argmax(out, axis=1)
        labels = np.argmax(y_train, axis=1)
        #np.set_printoptions(threshold=sys.maxsize)
        #print(preds)
        #print(labels)
        acc = np.mean(preds == labels)

        losses.append(loss)
        accuracies.append(acc)

        backward_pass(params, cache, y_train, lr)

        print(f"Epoch {epoch+1}/{epochs} - Loss: {loss:.4f} - Accuracy: {acc:.4f}")

    plt.figure(figsize=(12, 5))
    plt.subplot(1, 2, 1)
    plt.plot(range(1, epochs + 1), losses, label='Loss', color='orange')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()
    plt.grid(True)
    plt.title('Training Loss')

    plt.subplot(1, 2, 2)
    plt.plot(range(1, epochs + 1), accuracies, label='Accuracy', color='orange')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.legend()
    plt.grid(True)
    plt.title('Training Accuracy')

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
    args = parser.parse_args()

    X_train, y_train, label_map = load_dataset("dataset/train")
    input_size = X_train.shape[1]
    output_size = y_train.shape[1]
    params = initialize_weights(input_size, 128, 64, output_size)

    params = train(X_train, y_train, params, args.lr, args.epoch)

    with open("model.pkl", "wb") as f:
        pickle.dump((params, label_map), f)

