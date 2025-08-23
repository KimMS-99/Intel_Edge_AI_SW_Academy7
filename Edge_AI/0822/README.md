# 8월 22일

## How to improve accuracy (정확도를 높이는 방법)

0. Use Validation Set (검증 세트 사용)
    - 왜: 과적합 감지·하이퍼파라미터 선택이 정확해져 일반화↑.
    - 값 변화: 검증셋이 너무 작음 → 지표 요동. patience↑ → 학습 길어져 과적합 위험, ↓ → 조기 차단으로 미수렴 가능.
1. Batch Normalization (배치 정규화)
    - 왜: 분포를 정규화해 기울기 안정·큰 LR 사용 가능.
    - 값 변화: 배치 작음 → 통계 noisy(성능↓). momentum↑ → 통계 느리게 갱신, ↓ → 빠르게 반응. train/eval 모드 혼동 시 성능 급락.
2. Dropout Regularization (드롭아웃 정규화)
    - 왜: 공적응을 깎아 과적합↓, 일반화↑.
    - 값 변화: p↑(많이 끔) → 과소적합 위험. p↓ → 과적합 위험. Conv는 p 작게, FC는 조금 크게.
3. Learning Algorithm (학습 알고리즘)
    - 왜: 손실·샘플링·증강·커리큘럼·증류·EMA 등 훈련 절차 전반을 조절해 신호-잡음비↑ → 일반화↑.
4. Init Weight Value (가중치 초기화)
    - 왜: 초반 신호·기울기 폭주/소실 방지(He/Xavier).
    - 값 변화: 스케일↑ → 기울기 폭주, ↓ → 소실·학습정체. 활성함수에 맞는 초기화 필수.
5. Input Data Normalize (입력 정규화)
    - 왜: 특성 스케일을 맞춰 기울기 안정·수렴↑.
    - 값 변화: train 통계와 불일치(leak/잘못된 mean·std) → 검증 성능 왜곡/불안정. 정규화 전·후 증강 순서 바뀌면 효과 달라짐.
6. Learning Rate Scheduler (학습률 스케줄러)
    - 왜: 초반 탐색(높은 LR) → 후반 미세조정(낮은 LR)로 최소점 근접.
    - 값 변화: 감소 빠름 → 조기 고착, 느림 → 진동/미수렴. warmup 있음 → 초기 폭주 완화, 없음 → 초반 불안정 가능.

## dnn 실습

### [`MNIST_classification_DNNwithPytorch_Student.py`](./MNIST_classification_DNNwithPytorch_Student.py) 
- FashionMNIST로 완전연결 DNN을 학습·평가·시각화하고 모델 저장까지 한 번에 돌리는 실습 코드로 어제 했던 [ann 실습 코드](../0821/MNIST_classification_ANNwithPytorch.py)보다 정확도가 올라간것을 볼 수 있으며 flatten이 없는 것을 알 수 있다.
- 매 에폭 test_loader로 점검해 데이터 누설과 성능 과대평가가 발생하고 과적합 감지·최적 에폭 판단이 어려웠는데 [`MNIST_classification_DNNwithPytorch_Student_val.py`](./MNIST_classification_DNNwithPytorch_Student_val.py)이 코드에서는 학습셋을 Train/Val로 분할해 val_loader를 추가하고, 에폭마다 evaluate_model로 검증 성능만 확인·최고 모델 저장(베스트 체크포인트) → 최종에만 test 평가하고, 그래프에 Val loss/acc를 함께 그리도록 바꿨다.

## CNN
- 이미지 등 격자 구조 데이터에 특화된 합성곱 신경망. 작은 커널 + 가중치 공유로 지역 특징을 추출하고 파라미터 효율과 이동 등가성을 확보하며, 스트라이드·풀링으로 다운샘플링해 계층적 특징맵을 형성.
- 시각 과제(분류·검출·분할)에서 강력하고 엣지/실시간에도 유리. 다만 스케일·회전·장거리 문맥엔 한계가 있어 데이터 증강, BatchNorm/Dropout, Residual 연결, 1×1/Dilated/Depthwise 합성곱, (필요 시) 어텐션으로 보완.

### [`MNIST_classification_CNNwithPytorch.py`](./MNIST_classification_CNNwithPytorch.py)
- MNIST 손글씨를 CNN으로 학습·평가·시각화·모델 저장까지 한 번에 수행. 이전 ANN/DNN(완전연결) 실습보다 정확도가 잘 나오는 걸 확인할 수 있으며, 이유는 작은 커널+가중치 공유(지역성), MaxPool/Stride로 이동 변화에 강함, BN/Dropout/L2/Scheduler로 일반화와 학습 안정성을 높였기 때문.