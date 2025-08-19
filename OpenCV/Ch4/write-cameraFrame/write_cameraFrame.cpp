#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	VideoCapture capture(0); // 비디오 객체 선언 및 0번 카메라 연결
	CV_Assert(capture.isOpened());

	double fps = 29.97;									  // 초당 프레임 수
	int delay = cvRound(1000.0 / fps);					  // 프레임간 지연시간
	Size size(640, 360);								  // 동영상 파일 해상도
	int fourcc = VideoWriter::fourcc('D', 'X', '5', '0'); // 압축 코덱 설정

	capture.set(CAP_PROP_FRAME_WIDTH, size.width); // 해상도 설정
	capture.set(CAP_PROP_FRAME_HEIGHT, size.height);

	cout << "width x height : " << size << endl;
	cout << "VideoWriterfourcc : " << fourcc << endl;
	cout << "delay : " << delay << endl;
	cout << "fps : " << fps << endl;

	VideoWriter writer;
	writer.open("../image/video_file.avi", fourcc, fps, size); // 파일 개방 및 설정
	CV_Assert(writer.isOpened());

	for (;;)
	{
		Mat frame;
		capture >> frame; // 카메라 영상받기
		writer << frame;  // 프레임을 동영상으로 저장
		// writer.write(frame);

		imshow("카메라 영상보기", frame);
		if (waitKey(delay) >= 0)
			break;
	}
	return 0;
}