import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime

def main(log_file="log_results.csv"):
    df = pd.read_csv(log_file)

    # 날짜 문자열을 datetime으로 변환
    df["timestamp"] = pd.to_datetime(df["timestamp"], format="%Y-%m-%d %H:%M:%S")
    df["infer_acc"] = pd.to_numeric(df["infer_acc"], errors='coerce')
    df["val_acc"] = pd.to_numeric(df["val_acc"], errors='coerce')

    plt.figure(figsize=(14, 10))

    # 1. Learning Rate vs Inference Accuracy
    plt.subplot(2, 2, 1)
    plt.scatter(df["lr"], df["infer_acc"], c='blue', alpha=0.7)
    plt.xlabel("Learning Rate")
    plt.ylabel("Inference Accuracy (%)")
    plt.title("Learning Rate vs Inference Accuracy")
    plt.grid(True)

    # 2. Batch Size vs Inference Accuracy
    plt.subplot(2, 2, 2)
    plt.boxplot(
        [df[df["batch_size"] == bs]["infer_acc"].dropna() for bs in sorted(df["batch_size"].unique())],
        labels=sorted(df["batch_size"].unique())
    )
    plt.xlabel("Batch Size")
    plt.ylabel("Inference Accuracy (%)")
    plt.title("Batch Size vs Inference Accuracy")
    plt.grid(True)

    # 3. Validation Accuracy vs Inference Accuracy
    plt.subplot(2, 2, 3)
    plt.scatter(df["val_acc"], df["infer_acc"], c='green', alpha=0.7)
    plt.xlabel("Validation Accuracy (%)")
    plt.ylabel("Inference Accuracy (%)")
    plt.title("Validation vs Inference Accuracy")
    plt.grid(True)

    # 4. 시간에 따른 Inference Accuracy
    plt.subplot(2, 2, 4)
    plt.plot(df["timestamp"], df["infer_acc"], marker='o', linestyle='-')
    plt.xlabel("Timestamp")
    plt.ylabel("Inference Accuracy (%)")
    plt.title("Inference Accuracy Over Time")
    plt.xticks(rotation=30)
    plt.grid(True)

    plt.tight_layout()
    plt.savefig("visualization_results.png")
    plt.show()

if __name__ == "__main__":
    main()

