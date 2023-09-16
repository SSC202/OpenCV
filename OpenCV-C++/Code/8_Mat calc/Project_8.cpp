#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	float a[12] = { 1,2,3,4,5,10,6,7,8,9,10,0 };

	Mat mat_1 = Mat(3, 4, CV_32FC1, a);
	Mat mat_2 = Mat(2, 3, CV_32FC2, a);

	double minVal, maxVal;
	Point minIdx, maxIdx;

	//��ͨ����ȡ
	minMaxLoc(mat_1, &minVal, &maxVal, &minIdx, &maxIdx);
	cout << "��СֵΪ��" << minVal << " λ��Ϊ��" << minIdx << endl;
	cout << "���ֵΪ��" << maxVal << " λ��Ϊ��" << maxIdx << endl;

	//��ͨ����ȡ
	Mat remat_2 = mat_2.reshape(1, 4);
	minMaxLoc(remat_2, &minVal, &maxVal, &minIdx, &maxIdx);
	cout << "��СֵΪ��" << minVal << " λ��Ϊ��" << minIdx << endl;
	cout << "���ֵΪ��" << maxVal << " λ��Ϊ��" << maxIdx << endl;

	Scalar Mean;

	Mean = mean(mat_1);
	cout << Mean[0] << endl;

	Mat M_Mean, stddev;
	meanStdDev(mat_2, M_Mean, stddev);

	cout << "Mean = " << M_Mean << "stddev = " << stddev << endl;
	system("pause");

	return 0;
}