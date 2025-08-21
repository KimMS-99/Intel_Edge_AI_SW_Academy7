# class_distribution.py

import os

def count_images_per_class(base_path):
    class_counts = {}
    total = 0

    for class_name in sorted(os.listdir(base_path)):
        class_path = os.path.join(base_path, class_name)
        if not os.path.isdir(class_path):
            continue

        num_images = len([
            f for f in os.listdir(class_path)
            if os.path.isfile(os.path.join(class_path, f))
        ])
        class_counts[class_name] = num_images
        total += num_images

    return class_counts, total

def print_distribution():
    base_path = "dataset/train"
    counts, total = count_images_per_class(base_path)

    print(f"{'Class':<20} {'Count':<10} {'Ratio (%)':<10}")
    print("-" * 40)
    for cls, cnt in counts.items():
        ratio = (cnt / total) * 100 if total > 0 else 0
        print(f"{cls:<20} {cnt:<10} {ratio:.2f}%")
    print("-" * 40)
    print(f"{'Total':<20} {total:<10}")

if __name__ == "__main__":
    print_distribution()

