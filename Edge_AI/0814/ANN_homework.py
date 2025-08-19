import numpy as np
from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split
import pickle
import matplotlib.pyplot as plt
import scipy as sp
from types import SimpleNamespace
from tqdm import tqdm


class ANN:
    def __init__(self):
        self.layers = []
        self.Ytgt = []
        self.Ypred = []
        self.input_data = 0
        self.input_target = 0
        self.input_dims = 0
        self.n, self.w, self.h = 0, 0, 0
        self.Batch = 0
        self.__layernum = 0
        self.cache = []
        self.lr = 1e-3
        self.loss_scores = []

    def show(self):
        for i in range(len(self.layers)):
            if self.layers[i].property == 'param':
                print(self.layers[i].name, '\t weight :', self.layers[i].params[f'w{i}'].shape, '\t bias :', self.layers[i].params[f'b{i}'].shape)
            else:
                print(self.layers[i].name)

    def __add_layer(self, name, dim):
        layer = SimpleNamespace()
        layer.name = name
        layer.dim = dim
        if layer.name == 'flatten':
            layer.property = 'function'
        elif dim == 0:
            layer.property = 'activation'
            layer.params = {'act': name}
        else:
            layer.property = 'param'
            layer.params = dict()
            layer.grads = dict()
        self.layers.append(layer)

    def __param_init(self):
        input_dims = self.input_data.reshape(self.input_data.shape[0], -1).shape[1]
        nn = len(self.layers)
        for i in range(nn):
            if self.layers[i].property == 'param':
                output_dims = self.layers[i].dim
                self.layers[i].params[f'w{i}'] = np.random.uniform(-1, 1, (input_dims, output_dims))
                self.layers[i].params[f'b{i}'] = np.zeros((1, output_dims))
                self.layers[i].grads[f'w{i}'] = np.zeros((input_dims, output_dims))
                self.layers[i].grads[f'b{i}'] = np.zeros((1, output_dims))
                input_dims = output_dims
            elif self.layers[i].property == 'function':
                _, input_dims = self.__Flatten(self.input_data)
                continue
            elif self.layers[i].property == 'activation':
                continue

    def __Flatten(self, input):
        output = input.reshape(input.shape[0], -1)
        output_dims = output.shape[1]
        return output, output_dims

    def __categorical_cross_entropy(self, Ytgt, Ypred):
        Ypred = np.clip(Ypred, 1e-15, 1-1e-15)
        m = Ytgt.shape[0]
        return -np.sum(Ytgt * np.log(Ypred)) / m

    def __sigmoid(self, input):
        return sp.special.expit(input)

    def __relu(self, input):
        return np.maximum(0, input)

    def __softmax(self, input):
        exp_input = np.exp(input - np.max(input, axis=1, keepdims=True))
        return exp_input / np.sum(exp_input, axis=1, keepdims=True)

    def __backward_activation(self, dA, cache, name):
        if name == 'relu':
            dZ = np.array(dA, copy=True)
            dZ[cache <= 0] = 0
            return dZ
        elif name == 'sigmoid':
            s = self.__sigmoid(cache)
            return dA * s * (1 - s)
        elif name == 'softmax':
            # Softmax + CrossEntropy를 함께 쓸 경우 미분이 단순화됨 (dA가 Ypred-Ytgt)
            return dA

    def __update_params(self):
        for i in range(len(self.layers)):
            if self.layers[i].property == 'param':
                self.layers[i].params[f'w{i}'] -= self.lr * self.layers[i].grads[f'w{i}']
                self.layers[i].params[f'b{i}'] -= self.lr * self.layers[i].grads[f'b{i}']

    def __backward(self):
        m = self.Ytgt.shape[0]
        dA = self.cache[-1] - self.Ytgt
        dZ = dA
        for i in reversed(range(len(self.layers))):
            if self.layers[i].property == 'activation':
                dZ = self.__backward_activation(dZ, self.cache[i], self.layers[i].name)
            elif self.layers[i].property == 'param':
                dw = np.matmul(self.cache[i-1].T, dZ) / m
                db = np.sum(dZ, axis=0, keepdims=True) / m
                w = self.layers[i].params[f'w{i}']
                dZ = np.matmul(dZ, w.T)
                self.layers[i].grads[f'w{i}'] = dw
                self.layers[i].grads[f'b{i}'] = db
        self.__update_params()

    def __add_activation_layer(self, name):
        self.__add_layer(name, 0)
        
    def __forward(self):
        _X = np.array(self.input_data)
        self.cache = []
        for i in range(len(self.layers)):
            if self.layers[i].property == 'function':
                if self.layers[i].name == 'flatten':
                    _X, outputdim = self.__Flatten(_X)
                    self.cache.append(_X)
            elif self.layers[i].property == 'param':
                w = self.layers[i].params[f'w{i}']
                b = self.layers[i].params[f'b{i}']
                _X = np.matmul(_X, w) + b
                self.cache.append(_X)
            elif self.layers[i].property == 'activation':
                act_name = self.layers[i].params['act']
                if act_name == 'relu':
                    _X = self.__relu(_X)
                elif act_name == 'sigmoid':
                    _X = self.__sigmoid(_X)
                elif act_name == 'softmax':
                    _X = self.__softmax(_X)
                self.cache.append(_X)
        self.Ypred = _X
        return _X

    def Flatten(self):
        self.__add_layer('flatten', 0)

    def add_ann_layer(self, dims):
        self.__add_layer('ANN layers', dims)

    def sigmoid(self):
        self.__add_activation_layer('sigmoid')

    def relu(self):
        self.__add_activation_layer('relu')

    def softmax(self):
        self.__add_activation_layer('softmax')

    def compile(self):
        self.__param_init()

    def Input(self, size):
        Batch, width, height = size
        self.input_data = np.zeros((Batch, width, height))

    def run(self, X, Y, batchsize=32):
        self.input_data = X
        self.Ytgt = Y
        self.Batch = batchsize
        
        total_loss = 0
        num_batches = 0
        
        for i in tqdm(range(0, len(X), batchsize), desc="Training"):
            self.input_data = X[i:i+batchsize]
            self.Ytgt = Y[i:i+batchsize]
            
            # Forward pass
            ypred = self.__forward()
            
            # Loss 계산
            loss = self.__categorical_cross_entropy(self.Ytgt, ypred)
            total_loss += loss
            num_batches += 1
            
            # Backward pass
            self.__backward()
        
        # 평균 loss 출력
        avg_loss = total_loss / num_batches
        print(f"Average Loss: {avg_loss:.4f}")
        return avg_loss  
            

    


mnist = fetch_openml('mnist_784')
image = mnist.data.astype(np.float32)
label = mnist.target.astype(np.int64)

# TODO 데이터셋 분배
image_train, image_test, label_train, label_test = train_test_split(
    image, label,
    test_size=10000,       
    stratify=label,        
    random_state=42
)
def one_hot(labels, n_classes=10):
    m = labels.shape[0]
    oh = np.zeros((m, n_classes), dtype=np.float32)
    oh[np.arange(m), labels] = 1.0
    return oh


# TODO 데이터를 이미지 형태로 변경
image_train = np.array(image_train).reshape(-1, 28, 28) 
image_test  = np.array(image_test).reshape(-1, 28, 28)
label_train = one_hot(label_train, n_classes=10)
label_test  = one_hot(label_test , n_classes=10)
print("image_train : ", image_train.shape, "| image_test : ",image_test.shape, "| label_train : ",label_train.shape, "| label_test : ", label_test.shape)
image_train, image_test = image_train/255, image_test/255
# TODO 이미지 plot
# plt.figure()
# for i in range(12):
#     plt.subplot(3,4, i+1)
#     plt.imshow(image_train[i], cmap='gray')
#     plt.title(np.argmax(label_train[i]))
# plt.show()


# TODO ANN 클래스 선언 (중간까지 작성후 기능들이 원하는 대로 동작하는지 확인이 필요).
test_ANN=ANN()
# TODO 우선 layer를 쌓은 후
test_ANN.Input(size=image_train.shape) # batch width hight
test_ANN.Flatten()
test_ANN.add_ann_layer(128)
test_ANN.relu()
test_ANN.add_ann_layer(10)
test_ANN.softmax()
# TODO 학습 시킬 데이터를 입력
test_ANN.compile()

epoch = 50
for i in range(epoch):
    print(f"epoch {i}/{epoch}")
    test_ANN.run(image_train, label_train, batchsize=32)