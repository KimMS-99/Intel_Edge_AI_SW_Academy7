#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void camera_in();
void video_in();
void camera_in_video_out();

int main(void)
{
	camera_in();
	video_in();
	camera_in_video_out();

	return 0;
}

// 카메라 입력 처리
void camera_in()
{
	VideoCapture cap(0); // VideoCapture객체를 생성하고, 컴퓨터에 연결된 기본 카메라를 사용하도록 설정

	// 카메라 장치가 열렸는지 확인
	if (!cap.isOpened())
	{
		cerr << "Camera open failed!" << endl;
		return;
	}

	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	Mat frame, inversed;
	while (true)
	{
		cap >> frame; // 카메라 장치로부터 한 프레임을 받아와서 frame 변수에 저장.
		if (frame.empty())
			break;

		inversed = ~frame; // 현재 프레임 반전하여 inversed에 저장

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27) // ESC key
			break;
	}

	destroyAllWindows();
}

// 동영상 파일 처리
void video_in()
{
	VideoCapture cap("stopwatch.avi");

	if (!cap.isOpened())
	{
		cerr << "Video open failed!" << endl;
		return;
	}

	// 비디오 프레임의 가로 크기와 세로크기, 전페 프레임 수 출력
	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;

	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;

	// FPS 값으로부터 매 프레임 사이의 시간 간격을 밀리초 단위로 계산.
	int delay = cvRound(1000 / fps);

	Mat frame, inversed;
	while (true)
	{
		cap >> frame; // 카메라 장치로부터 한 프레임을 받아 와서 frame 변수에 저장.
		if (frame.empty())
			break;

		inversed = ~frame; // 현재 프레임을 반전하여 inversed 변수에 저장.

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27) // ESC key
			break;
	}

	destroyAllWindows();
}

// 카메라 입력을 반전하여 동영상 파일로 저장하기
void camera_in_video_out()
{
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cerr << "Camera open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(CAP_PROP_FPS);

	// DivX MPEG-4 코덱에 해당하는 fourcc 코드를 생성
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	// FPS 값으로부터 매 프레임 사이의 시간 간격을 밀리초 단위로 계산.
	int delay = cvRound(1000 / fps);

	// 저장할 도영상 파일 생성
	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));

	if (!outputVideo.isOpened())
	{
		cout << "File open failed!" << endl;
		return;
	}

	Mat frame, inversed;
	while (true)
	{
		cap >> frame; // 카메라 장치로부터 한 프레임을 받아 와서 frame 변수에 저장.
		if (frame.empty())
			break;

		inversed = ~frame;		 // 카메라 프레임을 반전하여 inversed 변수에 저장.
		outputVideo << inversed; // 반전된 카메라 프레임 영상 Inversed를 출력 동영상에 추가.

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}

	destroyAllWindows();
}
