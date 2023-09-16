#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void Read_Img(Mat& img, string str)
{
	img = imread(str);
	if (img.empty())
	{
		cout << "Fail to open :" << str << " " << endl;
		exit(-1);
	}
}

void drawLIne(Mat& img,                 //Ҫ��ǵ�ͼ��
    vector<Vec2f>lines,                 //����ֱ������
    double rows,                        //ԭͼ�������
    double cols,                        //ԭͼ�������
    Scalar scalar,                      //����ֱ�ߵ���ɫ
    int n                               //����ֱ�ߵ��߿�
)
{
    Point pt1, pt2;
    for (size_t i = 0; i < lines.size(); ++i) 
    {
        float rho = lines[i][0];                    //ֱ�߾�������ԭ��ľ���
        float theta = lines[i][1];                  //ֱ�߹�����ԭ�㴹����x��н�
        double a = cos(theta);                      //�нǵ�����ֵ
        double b = sin(theta);                      //�нǵ�����ֵ
        double x0 = a * rho, y0 = b * rho;          //ֱ��������ԭ�㴹�ߵĽ���
        double length = max(rows, cols);            //ͼ��߿�����ֵ

        //����ֱ���ϵ�һ��
        pt1.x = cvRound(x0 + length * (-b));
        pt1.y = cvRound(y0 + length * (a));
        //����ֱ������һ��
        pt2.x = cvRound(x0 - length * (-b));
        pt2.y = cvRound(y0 - length * (a));
        //�������һ��ֱ��
        line(img, pt1, pt2, scalar, n);
    }
}


int main()
{
	Mat img,edge;
	Read_Img(img, "picture.jpeg");

	Canny(img, edge, 50, 200);
	threshold(edge, edge, 170, 255, THRESH_BINARY);

	vector<Vec2f>lines;
	HoughLines(edge, lines, 1, CV_PI / 100, 50, 0, 0);

    Mat imgl;
    img.copyTo(imgl);
    drawLIne(imgl, lines, edge.rows, edge.cols, Scalar(255), 2);

    imshow("edge", edge);
    imshow("img", img);
    imshow("img1", imgl);
    waitKey(0);
    return 0;

}