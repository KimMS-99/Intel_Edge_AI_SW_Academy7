# 8월 19일

## labelImg
- 이미지 데이터에 객체의 위치와 클래스 정보를 라벨링할 수 있도록 도와주는 오픈소스 GUI Tool
- 가볍게 설치해서 사용할 수 있으나, 지원하는 format이 한정적
- YOLO, Pascal VOC format를 지원하고 있어, Object Detection 모델 학습 준비에 유용
- [깃허브 링크](https://github.com/HumanSignal/labelImg)

### 설치
```bash
mkdir labelimg
cd labelimg
python3 -m venv .venv
source .venv/bin/activate
pip install setuptools
pip install labelImg
```
### 실행방법
```bash
# 1
labelImg
# 2
labelImg [Image Path] [Class File] # ex) labelImg ./obj_train_data ./obj.name
```

## labelme
- 이미지에 다각형, 사각형, 원형 등 다양한 형태의 라벨링을 지원하는 오픈 소스 GUI Tool
- 비디오 데이터에서 라벨링 가능
- VOC (Semantic / Instance), COCO (Instance) Segmentation 지원
- [깃허브 링크](https://github.com/LabelMe/labelme)

### 설치
```bash
mkdir labelme
cd labelme/
python3 -m venv .venv
source .venv/bin/activate
pip install labelme 
```
### 실행방법
```bash
labelme
```

## Steps to run training and inferencing

```sh
labelme2yolo --json_dir ./cup/

ls -ahl cup/YOLODataset/dataset.yaml

git clone https://github.com/ultralytics/yolov5.git

python3 –m venv .venv
source .venv/bin/activate
pip install -r requirements.txt

python3 train.py --img 640 --batch 16 --epochs 50 --data /<YOLO dataset full path>/dataset.yaml --weights yolov5s.pt

python3 infer.py
```
