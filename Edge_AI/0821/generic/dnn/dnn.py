import numpy as np

def relu(x):
    return np.maximum(0, x)

def relu_deriv(x):
    return (x > 0).astype(float)

def softmax(x):
    e = np.exp(x - np.max(x, axis=1, keepdims=True))
    return e / np.sum(e, axis=1, keepdims=True)

def initialize_weights(input_size, hidden1, hidden2, hidden3, output_size):
    params = {
        "W1": np.random.randn(input_size, hidden1) * 0.1,
        "b1": np.zeros((1, hidden1)),
        "W2": np.random.randn(hidden1, hidden2) * 0.1,
        "b2": np.zeros((1, hidden2)),
        "W3": np.random.randn(hidden2, hidden3) * 0.1,
        "b3": np.zeros((1, hidden3)),
        "W4": np.random.randn(hidden3, output_size) * 0.1,
        "b4": np.zeros((1, output_size)),
    }
    return params

def forward_pass(x, params):
    z1 = x @ params["W1"] + params["b1"]
    a1 = relu(z1)
    z2 = a1 @ params["W2"] + params["b2"]
    a2 = relu(z2)
    z3 = a2 @ params["W3"] + params["b3"]
    a3 = relu(z3)
    z4 = a3 @ params["W4"] + params["b4"]
    out = softmax(z4)
    cache = {"x":x, "z1":z1, "a1":a1, "z2":z2, "a2":a2, "z3":z3, "a3":a3, "z4":z4, "out":out}
    return out, cache

def backward_pass(params, cache, y_true, lr, sample_weights=None):
    m = y_true.shape[0]
    dz4 = cache["out"] - y_true

    if sample_weights is not None:
       sample_weights = sample_weights.reshape(-1, 1)
       dz4 *= sample_weights

    dW4 = (cache["a3"].T @ dz4) / m
    db4 = np.sum(dz4, axis=0, keepdims=True) / m

    da3 = dz4 @ params["W4"].T
    dz3 = da3 * relu_deriv(cache["z3"])
    dW3 = (cache["a2"].T @ dz3) / m
    db3 = np.sum(dz3, axis=0, keepdims=True) / m

    da2 = dz3 @ params["W3"].T
    dz2 = da2 * relu_deriv(cache["z2"])
    dW2 = (cache["a1"].T @ dz2) / m
    db2 = np.sum(dz2, axis=0, keepdims=True) / m

    da1 = dz2 @ params["W2"].T
    dz1 = da1 * relu_deriv(cache["z1"])
    dW1 = (cache["x"].T @ dz1) / m
    db1 = np.sum(dz1, axis=0, keepdims=True) / m

    params["W4"] -= lr * dW4
    params["b4"] -= lr * db4
    params["W3"] -= lr * dW3
    params["b3"] -= lr * db3
    params["W2"] -= lr * dW2
    params["b2"] -= lr * db2
    params["W1"] -= lr * dW1
    params["b1"] -= lr * db1

