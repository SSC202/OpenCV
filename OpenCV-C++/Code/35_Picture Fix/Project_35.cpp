#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("picture.jpg");
	Mat img_mask;
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	imshow("img", img);


	//ת��Ϊ�Ҷ�ͼ
	Mat imgGray;
	cvtColor(img, imgGray, COLOR_RGB2GRAY, 0);


	//ͨ����ֵ��������Mask��ģ
	threshold(imgGray, img_mask, 200, 255, THRESH_BINARY);


	//��Mask���ʹ�������Mask���
	Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(img_mask, img_mask, Kernel);

	//ͼ���޸�
	Mat imgInpaint;
	inpaint(img, img_mask, imgInpaint, 5, INPAINT_NS);


	//��ʾ������
	imshow("imgMask", img_mask);
	imshow("imgInpaint", imgInpaint);
	waitKey();
	return 0;
}
