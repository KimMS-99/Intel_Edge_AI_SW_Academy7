# 8월 21일 실습

### [ANN](#ann) vs [DNN](#dnn)
| | [ANN](#ann) | [DNN](#dnn)
|:---:|:---:|:---:|
| 은닉층 | 2개 이하 | 3개 이상
| 구조 | 비교적 단순 | 깊고 복작
| 활용분야 | 기본적인 패턴 인식 | 복잡한 데이터(이미지, 음성 등)
| 장점 | 구현과 이해가 쉬움 | 복잡한 데이터 모델링에 강점
| 단점 | 복잡한 데이터 한계 및 과적합 | 학습시간, 해석 어려움

## ANN
- 인공 뉴런과 가중치로 이루어진 일반적인 신경망으로, 순전파·역전파·경사하강법으로 학습.
- 비선형 조합으로 복잡한 함수를 근사하지만, 데이터/정규화/최적화가 성능을 좌우.

### [`train-c01.py`](./generic/ann/train-c01.py)

`python3 ./train-c01.py --epoch 100 --lr 0.1`로 실행<br>
`python3 ./inference.py`로 실행 결과 얻기

| Epoch | Learning Rate(lr) | Result
|:---:|:---:|:---:|
| 100 | 0.01 | 41.25% (33/80)
| 1000 | 0.01 | 46.25% (37/80)
| 100 | 0.05 | 41.25% (33/80)
| 1000 | 0.05 | 46.25% (37/80)
| 100 | 0.1 | 47.50% (38/80)
| 1000 | 0.1 | 42.50% (34/80)
| 300 | 0.1 | 50.00% (40/80)

### [`train-c02.py`](./generic/ann/train-c02.py)

`python3 ./train-c02.py --epoch 100 --lr 0.1`로 실행<br>
`python3 ./inference.py`로 실행 결과 얻기
    
| Epoch | Learning Rate(lr) | Result
|:---:|:---:|:---:|
| 100 | 0.01 | 40.00% (32/80)
| 1000 | 0.01 | 41.25% (33/80)
| 100 | 0.05 | 37.50% (30/80)
| 1000 | 0.05 | 37.50% (30/80)
| 100 | 0.1 | 41.25% (33/80)
| 1000 | 0.1 | 41.25% (33/80)

### [`train-c03.py`](./generic/ann/train-c03.py)

`python3 ./train-c03.py --epoch 100 --lr 0.1 --use_class_weight`로 실행<br>
`python3 ./inference.py`로 실행 결과 얻기

| Epoch | Learning Rate(lr) | Result
|:---:|:---:|:---:|
| 100 | 0.01 | 38.75% (31/80)
| 1000 | 0.01 | 37.50% (30/80)
| 100 | 0.05 | 35.00% (28/80)
| 1000 | 0.05 | 35.00% (28/80)
| 100 | 0.1 | 41.25% (33/80)
| 1000 | 0.1 | 41.25% (33/80)
| 500 | 0.0445 | 46.25% (37/80)
| 1000 | 0.1115 | 46.25% (37/80)

### [`dataset_argument.py`](./generic/ann/dataset_argument.py)
기존 학습 데이터를 인위적으로 늘리기 위해 이미지에 다양한 변형을 적용. <br>
과적합 방지 데이터 부족 문제 해결

`dataset_argument.py` 를 실행하여 부족한 데이터에 데이터셋을 늘린다.<br>
`dataset_ratio.py` 를 실행하여 데이터의 개수가 모두 같은걸 확인한 후<br>
위에 코드(`train-c03.py`)를 실행하면 %가 오른것을 확인할 수 있다.

### BatchSize 적용
- Gradient의 노이즈 감소로 안정적 수렴
- 모델 성능 및 하이퍼파라미터 조정에 유리
- 빠른 학습과 하드웨어 자원 극대화
- 하드웨어 환경에 맞는 유연한 메모리 사용

- [`train-c04.py`](./generic/ann/train-c04.py)

`python3 ./train-c04.py --epoch 100 --lr 0.1 --use_class_weight --batch_size 32`로 실행<br>
`python3 ./inference.py`로 실행 결과 얻기

| Epoch | Learning Rate(lr) | Batch size |Result
|:---:|:---:|:---:|:---:|
| 100 | 0.01 | 32 | 51.25% (41/80)
| 100 | 0.01 | 8 | 52.50% (42/80)
| 100 | 0.05 | 32 | 56.25% (45/80)
| 100 | 0.05 | 8 | 56.25% (45/80)
| 100 | 0.1 | 32 | 48.75% (39/80)
| 100 | 0.1 | 8 | 53.75% (43/80)
| 100 | 0.035 | 32 | 57.50% (46/80)

## DNN
- 여러 은닉층을 쌓은 심층 신경망(ANN의 부분집합)으로, 계층적 표현 학습으로 고난도 과제에서 강력.
- 높은 표현력과 성능 대신, 훈련 안정화(활성화·정규화·스킵연결)와 자원 관리가 핵심 과제.

### [`train-c01.py`](./generic/dnn/train-c01.py)

`python3 ./train-c01.py --epoch 100 --lr 0.01 --use_class_weight --batch_size 32`로 실행<br>
`python3 ./inference.py`로 실행 결과 얻기

- Result
    - Dataset (Train/Val/Test) & Early stop
    - Imbalanced data (Class 가중치)
    - Augmentation
    - More data
    - batch_size 추가
    - 은닉층 추가 (DNN)

| Epoch | Learning Rate(lr) | Batch size |Result
|:---:|:---:|:---:|:---:|
| 100 | 0.01 | 64 | 47.50% (38/80)
| 100 | 0.01 | 32 | 47.50% (38/80)
| 100 | 0.05 | 64 | 42.50% (34/80)
| 100 | 0.05 | 32 | 51.25% (41/80)
| 100 | 0.1 | 64 | 52.75% (42/80)
| 100 | 0.1 | 32 | 51.25% (41/80)
| 100 | 0.035 | 64 | 46.25% (37/80)
| 100 | 0.035 | 32 | 52.50% (42/80)

**Pratice**
dropout 추가하여 실습해보기

## Pytorch

### Pytorch 쓰는 이유

1. 즉각적으로 실행한다.
2. 동적으로 신경망을 구성하면서 그래프를 그린다.
3. 분산 컴퓨팅
4. HARDWARE ACCELERATED INFERNCE
5. 단순화

### Pytorch Install & Environment

[Pytorch site](https://pytorch.org/) 보면서 설치(각종 정보도 있음)

**Check torch & torchvision installed**
```bash
# Simple check
$ python

import torch
print(torch.__version__)
import torchvision
print(torchvision.__version__)

# Check if installed
$ pip show torch
$ pip show torchvision

# List all torch packages
$ pip list | grep torch
```

**[How to use torch with GPU](./How_to_use_torch_with_GPU.py)**

### Pytorch Tensor
[`Tensor_test.py`](./Tensor_test.py) - 스칼라(0D)·벡터(1D)·행렬(2D)·3D 텐서를 만들고 각 shape와 dim()(차원 수) 값을 확인하는 코드<br>
[`Tensor_Attribution.py`](./Tensors_Attribution.py) - NumPy ↔ PyTorch 상호운용 & 메모리 레이아웃 실습하는 코드<br>
[`Autogard`](./Autograd.py) - PyTorch autograd 확인 코드
[visualize_graph.py](./visualize_graph.py) - 선형 모델의 순전파·역전파와 그래디언트 확인 + 연산 그래프 시각화 실습