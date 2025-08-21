import pickle
import numpy as np
from dnn import forward_pass
from utils import load_dataset
from sklearn.metrics import classification_report

X_test, y_test, label_map = load_dataset("dataset/test")
with open("model.pkl", "rb") as f:
    params, label_map = pickle.load(f)

out, _ = forward_pass(X_test, params)
preds = np.argmax(out, axis=1)
y_true = np.argmax(y_test, axis=1)

print(classification_report(y_true, preds, target_names=label_map.keys()))
