#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
    system("color F0");                                                 //�������������ɫ
    Mat img = imread("picture.jpeg");
    if (img.empty()) {
        cout << "Fail to open!" << endl;
        return -1;
    }
    imshow("ԭͼ", img);
    Mat gray, binary;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(3, 3), 2, 2);                         //ƽ���˲�
    threshold(gray, binary, 135, 255, THRESH_BINARY_INV);                   //����Ӧ��ֵ��

    //�������������
    vector<vector<Point>>contours;                                      //����
    vector<Vec4i>hierachy;                                              //��������ṹ����
    findContours(binary, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    //��������
    for (int i = 0; i < contours.size(); ++i) {
        drawContours(img, contours, i, Scalar(0, 0, 255), 2, 8);
    }

    //��������ṹ����
    for (int i = 0; i < hierachy.size(); ++i) {
        cout << hierachy[i] << endl;
    }
    //��ʾ���
    imshow("res", img);
    waitKey(0);
    return 0;
}
