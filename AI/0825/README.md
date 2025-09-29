# 8월 25일

## ResNet50
Residual Block(잔차 연결)을 도입해 깊은 신경망에서도 안정적으로 학습할 수 있도록 설계된 50층짜리 CNN 모델로, 이미지 분류와 다양한 비전 작업의 대표적인 백본(backbone)으로 널리 사용된다.

[`train.py`](./train.py) - PyTorch + torchvision의 ResNet50을 이용해서 ImageFolder 데이터셋으로 학습·검증하는 전체 파이프라인<br>
`inference.py` 로 결과 보기 - Overall Accuracy : 88.75% (71/80)

[`train-mod.py`](./pytorch/train-mod.py) - 커스텀 데이터셋을 MobileNetV2으로 학습하고 최적의 모델을 저장하는 PyTorch 기반 이미지 분류 학습 코드<br>
`inference-mod.py` 로 결과 보기 - Overall Accuracy : 80.00% (64/80)

## OTX

### Install OTX
```bash
sudo apt install curl
curl -LsSf https://astral.sh/uv/install.sh | sh
# source $HOME/.local/bin/env # 경로에 없으면 그냥 넘어가면 된다.
uv --help # 깔렸는지 확인
uv venv --ptyhon 3.10 .venv
source .venv/bin/activate

uv pip install otx[base]
otx -v
```

### OTX Quick Start

```bash
# 어떤 형태의 Deep Learning 학습을 진행할지 결정, 해당 Deep Learning 종류에 따른 Pretrained Model 들도 확인 및 결정
otx find --task DETECTION 

# Train
otx train --work_dir [Workspace Path] --data_root [Dataset Path] --config [Pretrained Model Path]
## ex)
otx train --work_dir otx-test --data_root animal-dataset/ --config /home/ubuntu03/Intel_class/venv/lib/python3.10/site-packages/otx/recipe/detection/atss_mobilenetv2.yaml
## 학습된 모델을 샘플 코드와 함께 베포
otx export --work_dir [Workspace Path] --export_demo_package true
## ex)
otx export --work_dir otx-test --export_demo_package true

# OTX Demo App
## 베포된 Demo app 압축 해제
unzip exportable_code.zip
## 패키지 설치
cd python
python3 -m venv .venv
source .venv/bin/activate
pip install -U pip
pip install wheel setuptools openvino==2025.1openvino-model-api==0.3.0.2 numpy==1.26.4
python3 ./setup.py install
## Demo app 실행
python3 demo.py –i [Input] --output [Output Path]

# Deploy
otx export --work_dir [Workspace Path] --export_demo_package true

# Demo
python3 demo.py –i [Input] --output [Output Path]
```

## OpenVINO
Intel의 AI 추론 최적화 툴킷으로, PyTorch·TensorFlow·ONNX 모델을 IR(Intermediate Representation)로 변환해 Intel CPU·iGPU·NPU 등에서 빠르고 가볍게 실행.<br>
장점: CPU만으로도 고속 추론 가능, 멀티 하드웨어 지원, 무료·오픈소스라 엣지/산업 환경에 최적.

```bash
git clone https://github.com/openvinotoolkit/openvino_notebooks.git
```