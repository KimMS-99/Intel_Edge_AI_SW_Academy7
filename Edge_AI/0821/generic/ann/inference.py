# inference.py

import numpy as np
from PIL import Image
import os
import pickle
from ann import forward_pass

def load_images_in_folder(folder):
    data = []
    filenames = []

    for file in os.listdir(folder):
        path = os.path.join(folder, file)
        try:
            img = Image.open(path).convert("L").resize((28, 28))
            arr = np.array(img).reshape(-1) / 255.0
            data.append(arr)
            filenames.append(file)
        except Exception as e:
            print(f"Error loading {file}: {e}")

    return np.array(data), filenames

def inference():
    with open("model.pkl", "rb") as f:
        params, label_map = pickle.load(f)

    id_to_label = {v: k for k, v in label_map.items()}

    test_root = "dataset/test"
    total_correct = 0
    total_samples = 0

    print("Detailed Inference Results\n==========================")

    for class_name in sorted(os.listdir(test_root)):
        folder = os.path.join(test_root, class_name)
        if not os.path.isdir(folder): continue

        X, filenames = load_images_in_folder(folder)
        if len(X) == 0:
            print(f"\n{class_name}: No images found.\n")
            continue

        out, _ = forward_pass(X, params)
        preds = np.argmax(out, axis=1)
        true_label = label_map[class_name]

        print(f"\nClass: {class_name}")
        print("-" * 40)
        correct = 0
        for i, pred in enumerate(preds):
            pred_label = id_to_label[pred]
            is_correct = pred == true_label
            mark = "✔️" if is_correct else "❌"
            print(f"{filenames[i]:25} → Predicted: {pred_label:15} {mark}")
            if is_correct:
                correct += 1

        total = len(preds)
        acc = correct / total * 100
        print(f"\n{class_name} Accuracy: {acc:.2f}% ({correct}/{total})")

        total_correct += correct
        total_samples += total

    print("\n==========================")
    print(f"Overall Accuracy : {total_correct / total_samples * 100:.2f}% ({total_correct}/{total_samples})")

if __name__ == "__main__":
    inference()

