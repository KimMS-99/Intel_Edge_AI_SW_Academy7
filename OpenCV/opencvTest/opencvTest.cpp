#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    cout << "Hello OpenCV " << CV_VERSION << endl;
    Mat img;
    img = imread("lenna.bmp"); // OpenCV에서 제공하는 함수로 bmp파일을 불러와서 img변수에 저장.
    // img = imread("lenna.bmp", IMREAD_GRAYSCALE);
    // img = imread("lenna.jpg");

    if (img.empty())
    {
        cerr << "Image load failed!" << endl;
        return 1;
    }

    namedWindow("image"); // 영상을 화면에 나타내기 위한 새로운 창을 생성하고, 그 창에 이름을 image로 설정.
    imshow("image", img); // "image"라는 이름의 창에 img 객체가 가지고 있는 lenna.bmp 영상을 출력함.
    vector<int> params;
    params.push_back(IMWRITE_JPEG_QUALITY);
    params.push_back(95);
    imwrite("lenna1.jpg", img, params);

    waitKey(1000);          // 사용자의 키보드 입력을 기다린다, 매개변수는 키 입력을 기다릴 시간(밀리초 단위)이며 0보다 작거나 같으면 무한히 기다린다
    destroyWindow("image"); // namedWindow()함수에 의해 생성된 출력 창을 닫을 수 있음.

    return 0;
}
