import subprocess
import time
import random
import csv
import argparse
from datetime import datetime

def run_training(lr, batch_size):
    cmd = [
        "python", "ann-train-c04.py",
        "--lr", str(lr),
        "--batch_size", str(batch_size),
        "--epoch", "2000",
        "--use_class_weight"
    ]
    print(f"Running training with lr={lr}, batch_size={batch_size}")
    subprocess.run(cmd)

def run_inference():
    result = subprocess.run(
        ["python", "ann-infer.py"],
        capture_output=True,
        text=True
    )
    output = result.stdout
    for line in output.splitlines():
        if "Overall Accuracy" in line:
            acc = float(line.split(":")[1].split("%")[0].strip())
            return acc
    return None

def main(duration_sec):
    start_time = time.time()
    log_file = "log_ann_results.csv"

    # 로그 파일 헤더
    if not open(log_file).readline():
        with open(log_file, "w", newline="") as f:
            writer = csv.writer(f)
            writer.writerow(["timestamp", "lr", "batch_size", "val_acc", "infer_acc"])

    while time.time() - start_time < duration_sec:
        lr = round(random.uniform(0.0001, 0.2), 5)
        batch_size = random.choice([32, 64, 128])

        run_training(lr, batch_size)

        # ann-train-c04.py가 val_acc를 all_dnn_results.txt에 저장함
        try:
            with open("all_dnn_results.txt", "r") as f:
                last_line = f.readlines()[-1]
                _, _, _, val_acc = last_line.strip().split(",")
                val_acc = float(val_acc)
        except Exception as e:
            val_acc = None
            print(f"Warning: Failed to read validation accuracy: {e}")

        infer_acc = run_inference()

        with open(log_file, "a", newline="") as f:
            writer = csv.writer(f)
            writer.writerow([
                datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                lr,
                batch_size,
                f"{val_acc:.4f}" if val_acc else "N/A",
                f"{infer_acc:.4f}" if infer_acc else "N/A"
            ])

        print(f"Logged: lr={lr}, batch_size={batch_size}, val_acc={val_acc}, infer_acc={infer_acc}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--duration", type=int, required=True, help="실행 시간 (초)")
    args = parser.parse_args()
    main(args.duration)

