#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("picture.jpg");
	if (img.empty())
	{
		cout << "Fail to open!" << endl;
		return -1;
	}

	//�����߿�
	Mat mask = Mat::zeros(Size(img.cols, img.rows), CV_8UC3);
	Rect rect(100, 100, 300, 300);
	mask(rect) = Scalar(255, 255, 255);

	Mat res1;
	min(mask, img, res1);
	imshow("��ͼ���", res1);

	//������Ĥ
	Mat rmask = Mat(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 255));

	Mat res2;
	min(rmask, img, res2);
	imshow("��Ĥ���", res2);
	waitKey();
	return 0;
	
}