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
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	//ֱ��ͼ��������
	Mat hist;
	const int channels[1] = { 0 };           //ͨ������
	float inRanges[2] = { 0,255 };
	const float* ranges[1] = { inRanges };   //���ػҶ�ֵ��Χ
	const int dims[1] = { 256 };             //ֱ��ͼά�ȣ����ػҶ�ֵ���ֵ��
	//ֱ��ͼ����
	calcHist(&img, 1, channels, Mat(), hist, 1, dims, ranges);

	//ֱ��ͼ����
	int hist_w = 512;
	int hist_h = 400;
	int width = 2;
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	for (int i = 1; i <= hist.rows; ++i)
	{
		rectangle(histImage, Point(width * (i - 1), hist_h - 1), Point(width * i - 1, hist_h - cvRound(hist.at<float>(i - 1) / 20)), Scalar(255, 255, 255), -1);
	}
	namedWindow("histImage", WINDOW_AUTOSIZE);
	imshow("histImage", histImage);
	imshow("gray", gray);
	waitKey(0);
	return 0;
}