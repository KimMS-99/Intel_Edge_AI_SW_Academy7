#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
    for (int i = 0; i < 10; i++)
    {
        VideoCapture cap(i);
        if (cap.isOpened())
        {
            cout << "카메라 장치 [" << i << "] 가 열렸습니다." << endl;
            Mat frame;
            cap.read(frame);
            imshow("Camera " + to_string(i), frame);
            waitKey(0);
            destroyWindow("Camera " + to_string(i));
        }
    }
    return 0;
}
