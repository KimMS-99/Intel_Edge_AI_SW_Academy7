import mglearn
import matplotlib.pyplot as plt
import numpy as np
from numpy.random import rand
X, Y = mglearn.datasets.make_wave(n_samples = 40)
# 학습 알고리즘을 사용하지 않고 선형 회귀 구현

# 모델 함수 정의 모델 함수 y = w*x + b
def Model_fnc(x,weight,bias):
    return np.matmul(x,weight)+ bias

# Linear regression class 정의
class Linear_regression():
    def __init__(self, Y, X, lr=0.01, n_iter=10000):
        self.Y = Y
        self.X = X
        self.lr = lr
        self.iter = n_iter
        
        self.weight = rand(1)   # (1,)
        self.bias = rand(1)     # (1,)
        self.model = Model_fnc

        self.history = {"loss": [], "w": [], "b": []}
        self.dw = 0.0
        self.db = 0.0

    # 오차 계산(loss)
    def mse(self, Ytgt, Ypred):
        return np.mean((Ytgt - Ypred) ** 2)

    # 예측값 계산
    def forward(self, weight, bias):
        # 모델을 통한 예측값 계산
        y_pred = self.model(self.X, weight, bias)
        # 오차구하기(손실)
        loss = self.mse(self.Y, y_pred)
        return y_pred, loss
    
    # gradient 구하기
    def grad_f(self, loss_prev, loss_curr, h):
        # 호출부가 (loss_plus, loss_curr)을 넣으므로 (loss_plus - loss_curr)/h
        return (loss_prev - loss_curr) / h
    
    # GD 알고리즘 적용
    def backward(self, loss_curr):
        h = 1e-6  # 너무 작으면 수치잡음↑, 너무 크면 부정확

        # weight의 gradient를 구하기
        _, loss_dw = self.forward(self.weight + h, self.bias)
        grad_w = self.grad_f(loss_dw, loss_curr, h)
         
        # bias의 gradient를 구하기
        _, loss_db = self.forward(self.weight, self.bias + h)
        grad_b = self.grad_f(loss_db, loss_curr, h)
         
        # gradient decent 알고리즘 적용
        prev_w = self.weight.copy()
        prev_b = self.bias.copy()
        
        self.weight = self.weight - self.lr * grad_w
        self.bias  = self.bias  - self.lr * grad_b

        # eary stop 을 위한 parameter의 차분값 저장
        self.dw = float(np.linalg.norm(self.weight - prev_w))
        self.db = float(np.linalg.norm(self.bias  - prev_b))
        return grad_w, grad_b
    
    def fit(self, verbose=True):
        # iteration 횟수만큼  반복 루프 생성
        for i in range(1, self.iter):
            # forward 실행
            _, loss = self.forward(self.weight, self.bias)

            # loss, weight, bias 저장
            self.history["loss"].append(float(loss))
            self.history["w"].append(float(self.weight[0]))
            self.history["b"].append(float(self.bias[0]))

            # backpropagation 실행
            self.backward(loss)
            if abs(self.dw) < 1e-9 and abs(self.db) < 1e-9:
                break

        return self.history   

# Linear_regression 선언
lr_model = Linear_regression(Y, X, lr=1e-2, n_iter=2000)

# === 학습 전(베이스라인) 예측/손실 ===
Y_pred0 = Model_fnc(X, lr_model.weight, lr_model.bias)
loss0 = lr_model.mse(Y, Y_pred0)

#Linear_regression 실행
history = lr_model.fit(verbose=False)

# iteration 에 따른 weight, bias, loss 가져오기
loss    = history["loss"]
weights = np.array(history["w"])
biases  = np.array(history["b"])

# === 학습 후 예측/손실 ===
Y_predf = Model_fnc(X, lr_model.weight, lr_model.bias)
lossf = lr_model.mse(Y, Y_predf)

#그래프로 구현
order = np.argsort(X[:, 0])
plt.figure()
plt.plot(X, Y, 'o', label='Target')
plt.plot(X[order, 0], Y_pred0[order], label=f'Loss : {loss0:.4f}', linewidth=2)   # 주황선(기본 스타일)
plt.plot(X[order, 0], Y_predf[order], label=f'Loss : {lossf:.4f}', linewidth=2)   # 초록선(기본 스타일)
plt.legend()
plt.title('Linear Regression (GD result)')
plt.savefig('result_with_learning.jpg')   # 저장은 show 이전
plt.show()

