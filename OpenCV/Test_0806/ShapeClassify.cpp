#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

struct colorInfoStruct
{
    String name;
    Scalar color;
    int count;
};

void setLabel(Mat &img, const vector<Point> &pts, const String &label)
{
    Rect rc = boundingRect(pts);
    // rectangle(img, rc, Scalar(0, 0, 255), 1);
    putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0));
}

void setColorLabel(Mat &img, const vector<Point> &pts, const struct colorInfoStruct *colorInfo)
{
    // 1. 도형 중심 좌표 계산
    Moments mu = moments(pts);
    if (mu.m00 == 0)
        return;

    Point center(mu.m10 / mu.m00, mu.m01 / mu.m00); // 중심

    // 2. 텍스트 설정
    int fontFace = FONT_HERSHEY_PLAIN;
    double fontScale = 1.2;
    int thickness = 1;
    String text = colorInfo->name;

    // 3. 글자 크기 계산
    Size textSize = getTextSize(text, fontFace, fontScale, thickness, 0);
    Point textOrg(center.x - textSize.width / 2, center.y + textSize.height / 2);

    // 4. 보색 계산
    Scalar textColor = colorInfo->color;
    Scalar bgColor(255 - textColor[0], 255 - textColor[1], 255 - textColor[2]);

    // 5. 배경 사각형 그리기 (글자 영역 기준)
    Point rectTopLeft = textOrg + Point(0, -textSize.height);
    Point rectBottomRight = textOrg + Point(textSize.width, textSize.height / 2);
    rectangle(img, rectTopLeft, rectBottomRight, bgColor, FILLED);

    // 6. 텍스트 출력
    putText(img, text, textOrg, fontFace, fontScale, textColor, thickness);
}

int main(int argc, char *argv[])
{
    colorInfoStruct colorInfo[4] = {
        {"blue", Scalar(255, 0, 0), 0},
        {"green", Scalar(0, 255, 0), 0},
        {"red", Scalar(0, 0, 255), 0},
        {"none", Scalar(128, 128, 128), 0}};
    // Mat img = imread("polygon.bmp", IMREAD_COLOR);
    Mat img = imread("640x480_shape.png", IMREAD_COLOR);

    if (img.empty())
    {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    imshow("gray", gray);

    Mat bin;
    threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);
    imshow("bin", bin);

    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    cout << "contours.size() : " << contours.size() << endl;

    for (int i = 0; i < contours.size(); i++)
    {
        vector<Point> pts = contours[i];

        vector<Point> approx;
        approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);

        int vtc = (int)approx.size();

        if (vtc == 3)
        {
            setLabel(img, pts, "triangle");
        }
        else if (vtc == 4)
        {
            setLabel(img, pts, "rectangle");
        }
        else if (vtc == 5)
            setLabel(img, pts, "pentagon");
        else if (vtc == 6)
            setLabel(img, pts, "hexagon");
        else
        {
            double len = arcLength(pts, true);
            double area = contourArea(pts);
            double ratio = 4. * CV_PI * area / (len * len);

            if (ratio > 0.85)
            {
                setLabel(img, pts, "circle");
            }
            else
            {
                setLabel(img, pts, "OVAL");
            }
        }

        Rect roiRect = boundingRect(pts);
        Mat roiBgr = img(roiRect);

        Mat roiHsv;
        cvtColor(roiBgr, roiHsv, COLOR_BGR2HSV);

        int cx = roiHsv.cols / 2;
        int cy = roiHsv.rows / 2;
        int roiSize = 16;

        int xStart = max(0, cx - roiSize / 2);
        int yStart = max(0, cy - roiSize / 2);
        int xEnd = min(roiHsv.cols, cx + roiSize / 2);
        int yEnd = min(roiHsv.rows, cy + roiSize / 2);

        Rect centerRect(xStart, yStart, xEnd - xStart, yEnd - yStart);
        Mat centerRoi = roiHsv(centerRect);

        Scalar meanHsv = mean(centerRoi);
        int colorIndex;

        if (170 <= meanHsv[0] || meanHsv[0] < 10) // Red
        {
            colorInfo[2].count++;
            colorIndex = 2;
        }
        else if (50 <= meanHsv[0] && meanHsv[0] < 70) // Green
        {
            colorInfo[1].count++;
            colorIndex = 1;
        }
        else if (110 <= meanHsv[0] && meanHsv[0] < 130) // Blue
        {
            colorInfo[0].count++;
            colorIndex = 0;
        }
        else
        {
            colorInfo[3].count++;
            colorIndex = 3;
        }
        setColorLabel(img, pts, &colorInfo[colorIndex]);
        drawContours(img, contours, i, Scalar(128, 128, 128), 2);
    }

    putText(img, "KMS", Point(20, 45), FONT_HERSHEY_PLAIN, 4, 0, 3);
    for (int i = 0; i < (sizeof(colorInfo) / sizeof(colorInfo[0])); i++)
    {
        vector<Point> pts = contours[i];

        String strText = colorInfo[i].name + " " + to_string(colorInfo[i].count);
        putText(img, strText, Point(20, 60 + (15 * i)), FONT_HERSHEY_PLAIN, 1, colorInfo[i].color, 1);
    }

    imwrite("KMS.png", img);
    imshow("img", img);
    waitKey();

    return 0;
}