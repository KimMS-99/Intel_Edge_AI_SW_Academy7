# utils.py
import os
import numpy as np
from PIL import Image

def preprocess_image(img_path):
    img = Image.open(img_path).convert("L").resize((28, 28))
    return np.array(img).flatten().astype(np.float32) / 255.0

def one_hot_encode(label_index, num_classes):
    one_hot = np.zeros(num_classes)
    one_hot[label_index] = 1.0
    return one_hot

def load_dataset(base_path):
    X, y = [], []
    label_map = {}
    for idx, label_name in enumerate(sorted(os.listdir(base_path))):
        label_map[label_name] = idx
        folder = os.path.join(base_path, label_name)
        for file in os.listdir(folder):
            img_path = os.path.join(folder, file)
            x = preprocess_image(img_path)
            X.append(x)
            y.append(one_hot_encode(idx, len(os.listdir(base_path))))
    return np.array(X), np.array(y), label_map

