#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<math.h>
using namespace std;
using namespace cv;

#define WIDTH 2
#define HIST_W 512
#define HIST_H 400
void createHist(Mat& img, Mat& hist);
void drawHist(Mat& hist, Mat& hist_dst, int type, string str, int width = WIDTH, int hist_h = HIST_H, int hist_w = HIST_W);

int main()
{
	Mat img = imread("picture.jpg");
	Mat f_img = imread("format.jpg");

	if (img.empty() || f_img.empty())
	{
		cout << "Fail to open!" << endl;
		return -1;
	}
	cvtColor(img, img, COLOR_BGR2GRAY);
	cvtColor(f_img, f_img, COLOR_BGR2GRAY);
	resize(f_img, f_img, Size(img.cols, img.rows));
	Mat hist, hist_f;
	createHist(img, hist);
	createHist(f_img, hist_f);
	drawHist(hist, hist, NORM_INF, "hist");
	drawHist(hist_f, hist_f, NORM_INF, "hist_f");

	//�����ۻ����ʾ���
	float hist1_cdf[256] = { hist.at<float>(0) };
	float hist2_cdf[256] = { hist_f.at<float>(0) };
	for (int i = 1; i < 256; ++i) {
		hist1_cdf[i] = hist1_cdf[i - 1] + hist.at<float>(i);
		hist2_cdf[i] = hist2_cdf[i - 1] + hist_f.at<float>(i);
	}
	//�����ۻ�����������
	float diff_cdf[256][256];
	for (int i = 0; i < 256; ++i) {
		for (int j = 0; j < 256; ++j) {
			diff_cdf[i][j] = fabs(hist1_cdf[i] - hist2_cdf[j]);
		}
	}
	//����LUTӳ���
	Mat lut(1, 256, CV_8U);
	for (int i = 0; i < 256; ++i) {
		//����Դ�Ҷȼ�Ϊi��ӳ��Ҷ�
		//��i���ۻ����ʲ�ֵ����С�Ĺ涨�Ҷ�
		float min = diff_cdf[i][0];
		int index = 0;
		//Ѱ���ۻ�������������ÿһ���е���Сֵ
		for (int j = 1; j < 256; ++j) {
			if (min > diff_cdf[i][j]) {
				min = diff_cdf[i][j];
				index = j;
			}
		}
		lut.at<uchar>(i) = (uchar)index;
	}
	Mat r_hist, res;
	LUT(img, lut, res);
	imshow("img", img);
	imshow("format", f_img);
	imshow("result", res);
	createHist(res, r_hist);
	drawHist(r_hist,r_hist, NORM_L1, "r_hist");
	waitKey();



	return 0;
}

void createHist(Mat& img, Mat& hist)
{
	const int channel[1] = { 0 };
	float inrange[2] = { 0,255 };
	const float* range[1] = { inrange };
	const int dims[1] = { 256 };
	calcHist(&img, 1, channel, Mat(), hist, 1, dims, range);
}

void drawHist(Mat& hist, Mat& hist_dst, int type, string str, int width, int hist_h, int hist_w)
{
	Mat Img_image = Mat::zeros(hist_h, hist_w, CV_8UC3);
	normalize(hist, hist_dst, 1, 0, type, -1, Mat());
	for (int i = 1; i <= hist.rows; ++i)
	{
		rectangle(Img_image, Point(width * (i - 1), hist_h - 1), Point(width * i - 1, hist_h - cvRound(hist_h * hist_dst.at<float>(i - 1)) - 1), Scalar(255, 255, 255), -1);
	}
	imshow(str, Img_image);
}