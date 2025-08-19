import numpy as np
import scipy as sp
from numpy.random import rand

xdata = np.array([[0, 0],[0, 1],[1, 0],[1, 1]])
ydata = np.array([0, 1, 1, 0])

class Perceptron():
    def __init__(self, X, Y, lr = 0.1, iteration = 5000, epoch = 300):
        self.X = X
        self.Y = Y

        self.lr = lr # 학습률(learning rate), 경사하강법에서 업데이트 크기
        self.__init_param__()       
        
        self.epoch = epoch
        self.iteration = iteration # 반복 횟수
        self.cache = [] # 각 레이어를 저장하기 위한 cache
    
    def __init_param__(self):
        # TODO 1-1. weight (2)
        # TODO 2-1 weight (2,2) + 
        self.weight1 = np.random.uniform(-1, 1, (2, 2))
        # TODO 2-2 weight(2)
        self.weight2 = np.random.uniform(-1, 1, (2))     #np.random.uniform(-1, 1, (4))
        # TODO 1-2. bias(1)
        # TODO 2-3. bias(2)
        self.bias1 = np.zeros((2))
        # TODO 2.4. bias(1)
        self.bias2 = np.zeros((1))

    def Linear(self, X, weight, bias): # Linear model
        output = np.matmul(X , weight.T) + bias
        return output
    
    def __backward_sigmoid(self, ZZ):
        alpha = 1/(1+np.exp(ZZ))
        return alpha*(1-alpha)

    def activation(self, X): # sigmoid, 활성화 함수
        return sp.special.expit(X)
    
    def loss(self, Ytgt, Ypred): #categorical
        return -np.mean(Ytgt*np.log(Ypred) + (1-np.array(Ytgt))*np.log(1-Ypred))
    
    def run(self):
        Global_loss_score = []

        # for i in range(1):#range(self.iteration):
        for ep in range(self.epoch):
            # self.__init_param__()
            for i in range(self.iteration):
                # TODO forward layer 1
                input = np.array(self.X)
                output = self.Linear(input, self.weight1, self.bias1)
                output = self.activation(output)
                cache = output # [-1]                
                input = output.copy()
                # TODO forward layer 2
                output = self.Linear(input, self.weight2, self.bias2)
                input = output.copy()
                Ypred = self.activation(input)
                # print(Ypred)           
                loss = self.loss(self.Y, Ypred)
                
                # dL/dw =  dL/dY * dY /dw  = dZ * X = dZ * cache      
                # X   [Batch, dims_input]
                # dZ  [Batch, dim_output]
                # dw  [dims_input, dim_output]
                # TODO Backpropagation sigmoid + binary crossentropy
                dZ = Ypred - self.Y # dL/dY
                # TODO Backpropagation layer 2
                
                dw2 = np.matmul(cache.T, dZ)
                db2 =np.mean(dZ, axis=0)
                # TODO dZ update
                # dL /dw = dL/dY * dY/dX *  dX / dw 
                dZ = dZ[:, np.newaxis] * self.weight2
                # dL /dw = dL/dY * dY/dX *  dX / dw 
                # dL / dact * dact / dw = 
                # [dL/dY * dY/dX] *  dX / dact * dact / dw
                # X = self.cache[-3]
                # back_act = self.__backward_sigmoid(X)
                back_act = cache*(1-cache)
                dZ = dZ * back_act
                # TODO Backpropagation 1
                
                dw1 = np.matmul(self.X.T, dZ)
                db1 =np.mean(dZ, axis=0)
                
                # print("loss : ", loss)
                self.weight1 = self.weight1  - self.lr*dw1
                self.bias1 = self.bias1      - self.lr*db1
                self.weight2 = self.weight2  - self.lr*dw2
                self.bias2 = self.bias2      - self.lr*db2           
            
            Global_loss_score.append([loss, self.weight1, self.bias1, self.weight2, self.bias2])
        return Global_loss_score


epoch = 20
epochs = np.linspace(1, 20, 20)
ANDgate = Perceptron(xdata, ydata, epoch=epoch)
history = ANDgate.run()
loss    = [h[0] for h in history]
weight1 = [h[1] for h in history]
weight2 = [h[3] for h in history]
bias1   = [h[2] for h in history]
bias2   = [h[4] for h in history]

index = np.argmin(loss)
print(index, loss[index])

o1 = ANDgate.Linear(xdata, weight1[index], bias1[index])
o1 = ANDgate.activation(o1)
o2 = ANDgate.Linear(o1, weight2[index], bias2[index])
output = ANDgate.activation(o2)

import matplotlib.pyplot as plt
plt.figure()
plt.plot(epochs, loss)
plt.show()

Ypred = (output>=0.5).astype(int)
print("----------------------------------")
print("Target | Predict")
print("----------------------------------")
for i in range(4):
    print(ydata[i], "     |",  Ypred[i])