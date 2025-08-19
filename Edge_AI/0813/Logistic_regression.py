import numpy as np
import mglearn
import matplotlib.pyplot as plt
import scipy as sp
from numpy.random import rand

X, Y = mglearn.datasets.make_forge()
mglearn.discrete_scatter(X[:,0],X[:,1],Y)
plt.legend(["Class  0","Class 1"],loc=4)
#plt.show()

def Model_fnc(X, weight, bias):
    Z = np.matmul(X , weight) + bias
    return sp.special.expit(Z)

# Logistic regerrsion class 정의
class Logistic_regression():
    def __init__(self, Y, X, lr=0.1, n_iter=20000):
        self.Y = Y
        self.X = X
        self.lr = lr

        self.iter = n_iter
        self.weight = rand(2)
        self.bias = rand(1)
        
        self.prev_weight = self.weight + 1e-3
        self.prev_bias = self.bias + 1e-3
        self.db = 1e9
        self.dw = 1e9*np.ones((2,1))
        self.loss_prev = 1e9
        
        self.history = []

    # 모델 함수 정의 (sigmoid)
    def Model_fnc(self, weight, bias):
        Z = np.matmul(self.X , weight) + bias
        return sp.special.expit(Z)
        #return [-sp.stats.log(sp.special.expit(Z)) + -sp.stats.log(sp.special.expit(Z))]
   
    # 오차 계산(loss)
    def categorical_cross_entropy(self, Ytgt, Ypred):
        Ypred = np.clip(Ypred, 1e-15, 1-1e-15)
        return -np.mean(Ytgt*np.log(Ypred) + (1-Ytgt)*np.log(1-Ypred))
    
    def loss(self, weight, bias, Ytgt):
        Ypred = self.Model_fnc(weight, bias)
        return self.categorical_cross_entropy(Ytgt, Ypred)

    # gradient 구하기.
    def grad_f(self, loss_prev, loss_curr, div):
        return (loss_prev - loss_curr)/(div)
    
    # 순전파 구하기.    
    def forward(self, weight, bias):
        # TODO 모델을 통한 예측값 계산e 
        y_pred = self.Model_fnc(weight, bias)
        # TODO 오차 구하기 (손실)
        loss = self.categorical_cross_entropy(self.Y, y_pred)
        return y_pred, loss

    # 역전파 구하기. (GD알고리즘 이용)
    def backward(self, loss_curr):
        h = 1e-4
        # eary stop 을 위한 parameter의 차분값 저장.
        # self.dw = self.weight -self.prev_weight
        # self.db = self.bias - self.prev_bias
        
        # weight의 gradiant를 구하기.
        loss_dw0 = self.loss(self.weight+np.array([h,0]), self.bias, self.Y)
        loss_dw1 = self.loss(self.weight+np.array([0,h]), self.bias, self.Y)
        grad_w_vec0 = self.grad_f(loss_dw0, loss_curr, h) 
        grad_w_vec1 = self.grad_f(loss_dw1, loss_curr, h)
        grad_w = np.array([np.mean(grad_w_vec0), np.mean(grad_w_vec1)])

        # bias의 gradiant를 구하기.
        loss_dh = self.loss(self.weight, self.bias+h, self.Y)
        grad_b_vec = self.grad_f(loss_dh, loss_curr, h)     
        grad_b = np.mean(grad_b_vec)
        # 이전 업데이트.
        self.loss_prev = loss_curr

        # gradiant decent 알고리즘 적용.
        self.weight = self.weight - self.lr * grad_w
        self.bias = self.bias - self.lr * grad_b

        # print(grad_w_vec, grad_b_vec)

    def fit(self, verbose=True):
        # iteration 횟수만큼 반복 루프 생성
        for i in range(1, self.iter):
            # 그 외 (i > 1) 순전파 및 역전파 실행

            y_pred, loss = self.forward(self.weight, self.bias)
            self.history.append([loss, self.weight, self.bias])
            self.backward(loss)

            # eary stop
            # if abs(self.dw[0]) < 1e-9 and abs(self.dw[1]) < 1e-9 and abs(self.db) <1e-9:
            #     break
        return self.history    

# Logistic_regression 선언
cLr = Logistic_regression(Y, X)

# Linear_regression 실행
history = cLr.fit()

# iteration 에 따른 weight, bias, loss 가져오기.
loss   = [h[0] for h in history]
weights = np.array([h[1] for h in history])
biases  = np.array([h[2] for h in history])
loss_ini = loss[3]
loss_mid = loss[500]
loss_ter = loss[-1]
print(loss_ini, loss_ter)
# 2) 그리드 생성
x_min, x_max = X[:,0].min() - .5, X[:,0].max() + .5
y_min, y_max = X[:,1].min() - .5, X[:,1].max() + .5
xx = np.linspace(x_min, x_max, 200)
yy = np.linspace(y_min, y_max, 200)
XX, YY = np.meshgrid(xx, yy)
grid = np.c_[XX.ravel(), YY.ravel()]

# 3) 확률 계산
Z_init  = Model_fnc(grid, weights[2],  biases[2]).reshape(XX.shape)
Z_mid  = Model_fnc(grid, weights[500],  biases[500]).reshape(XX.shape)
Z_mid2  = Model_fnc(grid, weights[13000],  biases[13000]).reshape(XX.shape)
Z_final = Model_fnc(grid, weights[-1], biases[-1]).reshape(XX.shape)

# 4) 플롯
plt.figure()
mglearn.discrete_scatter(X[:,0],X[:,1],Y)
# 4.2) decision boundary
c1=plt.contour(XX, YY, Z_init,  levels=[0.5], colors='green',  linestyles='--')
c2=plt.contour(XX, YY, Z_mid,  levels=[0.5], colors='blue',  linestyles='--')
c2=plt.contour(XX, YY, Z_mid2,  levels=[0.5], colors='blue',  linestyles='--')
c3=plt.contour(XX, YY, Z_final, levels=[0.5], colors='red',   linestyles='-')
# legend를 위한 dummy라인
from matplotlib.lines import Line2D
proxy_init  = Line2D([0], [0], color='green', linestyle='--', linewidth=2)
proxy_mid   = Line2D([0], [0], color='blue',  linestyle='--', linewidth=2)
proxy_final = Line2D([0], [0], color='red',   linestyle='-',  linewidth=2)
# 5) 범례
plt.legend(
    ['class 0', 'class 1', 'dd', 'dd', 'dd'],
    loc='lower right'
)
plt.show()