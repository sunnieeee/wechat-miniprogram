//#include<iostream>
//#include<opencv2\opencv.hpp>
//using namespace cv;
//using namespace std;
//
////����ȫ�ֱ���
//Mat g_srcImage,srcImage,g_templateImage,g_resultImage;
//
//
//int main()
//{
//	//������Ϸ��ͼ��Ŀ��ģ��
//	g_srcImage = imread("1.png", 1);
//	g_templateImage = imread("template.jpg", 1);
//	namedWindow("0", WINDOW_KEEPRATIO);                                  //�������namedwindowֱ��autosize�򲻿ɵ��ڴ�С����ʾ������
//	namedWindow("1", WINDOW_KEEPRATIO);
//	imshow("0", g_srcImage);
//	imshow("1", g_templateImage);
//	//�洢ԭ��Ϸ��ͼ
//	g_srcImage.copyTo(srcImage);                                         //����g_srcimage����ͼƬ����
//	//��ʼ�����ڽ������ľ���
//	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
//	int resultImage_cols = g_srcImage.rows - g_templateImage.cols + 1;
//	g_resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1);
//	//��matchTemplate��������ƥ��
//	matchTemplate(g_srcImage, g_templateImage, g_resultImage, TM_SQDIFF);//��6��ƥ�䷽��
//	namedWindow("2", WINDOW_KEEPRATIO);
//	imshow("2", g_resultImage);
//	//��׼��
//	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());
//	namedWindow("3", WINDOW_KEEPRATIO);
//	imshow("3", g_resultImage);
//	//ͨ������minMaxLoc��λ��ƥ���λ��
//	double minValue, maxValue ;
//	Point minLocation, maxLocation;
//	Point matchLocation;
//	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());   //Mat()��ʾ������Ĥ
//	matchLocation = minLocation;                  //SQDIFFԽС����ֵ�и��ߵ�ƥ���� ��matchlocation��g_template�������Ͻǵ�
//	//���ƾ���
//	rectangle(g_srcImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), Scalar(0, 0, 225), 5);
//	rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), Scalar(0, 0, 225), 5);  //���һ�����Ϊthickness
//	//��ʾƥ����
//	namedWindow("4", WINDOW_KEEPRATIO);
//	namedWindow("5", WINDOW_KEEPRATIO);
//	imshow("4", g_srcImage);
//	imshow("5", g_resultImage);
//	//���С�����ڶյĵ�
//	circle(g_srcImage, Point(matchLocation.x + g_templateImage.cols/2, matchLocation.y + g_templateImage.rows), 15, Scalar(225,225,0),-1);   //radius��color��thickness����Ϊ������ʵ��Բ �������Ͻǵĵ����ױ��е������任
//	namedWindow("6", WINDOW_KEEPRATIO);
//	imshow("6", g_srcImage);
//	
//	
//
//	
//	//ת�Ҷ�ͼ�����Ե���
//	Mat gray;
//	cvtColor(srcImage, gray, COLOR_BGR2GRAY);
//	GaussianBlur(gray, gray, Size(3, 3),5);
//	Canny(gray,gray , 3, 9);        //�ߵ��ͺ�����ֵ
//	namedWindow("7", WINDOW_KEEPRATIO);
//	imshow("7", gray);
//	//��С������������Ϊ��ɫ
//	Mat imageROI1;
//	imageROI1 = gray(Rect(matchLocation.x, matchLocation.y, g_templateImage.cols, g_templateImage.rows));
//	imageROI1 = { Scalar(0,0,0) };
//	namedWindow("8", WINDOW_KEEPRATIO);
//	imshow("8", gray);
//	//�ü���Ŀ�����򣬱������
//	Mat imageROI2;
//	imageROI2 = gray(Rect( 0,450 ,srcImage.cols,matchLocation.y-300));           //rows�У�cols�У��������Ͻ����꣬���γ�����,���Ӧ��С��Ϊ�ο��ž���������
//	namedWindow("9", WINDOW_KEEPRATIO);
//	imshow("9", imageROI2);
//
////	cout << (int)srcImage.at<uchar>(90,90) << "33" << endl;      //����Ҫ����int���͵�ǿ��ת��
//	int i, j, flag = 1;
//	Point max1=Point(0,0), max2=Point(0,0);
//	for (j= 0; j<580; j++)
//	{
//		if (flag)
//		{
//			for (i= 0; i<580; i++)
//			{
//				if ((int)imageROI2.at<uchar>(j, i) == 255)
//				{
//					max1 = Point(i,j );
//					flag = 0;
//					break;
//				}
//			}
//		}
//		else
//		{
//			break;
//		}
//	}          //��������С�ĵ�max1
//	flag = 1;
//	for (i= 580; i>0; i--)
//	{
//		if (flag)
//			for (j= 0; j < 580 ; j++)
//			{
//				if ((int)imageROI2.at<uchar>(j, i) == 255)
//				{
//					max2 = Point(i, j);
//					flag = 0;
//					break;
//				}
//			}
//		else
//		{
//			break;
//		}
//	}        
//	
//	/*//��������������ֵΪ255����������С�ͺ��������ĵ�
//	int i, j,flag=1;
//	Point max1 ,max2;
//	for (i = 0; i < imageROI2.rows; i++)
//	{
//		if (flag)
//		{
//			for (j = 0; j < imageROI2.cols; j++)
//			{
//				if (imageROI2.at<uchar>(j, i) == 255)
//				{
//					max1 = Point(j, i);
//					flag = 0;
//					break;
//				}
//			}
//		}
//		else
//		{
//			break;
//		}
//	}          //��������С�ĵ�max1
//	flag = 1;
//	for (j = imageROI2.cols; i>0; i--)
//	{
//		if(flag)
//		for (i = 0; i < imageROI2.rows; i++)
//		{
//			if (imageROI2.at<uchar>(j, i) == 255)
//			{
//				max2 = Point(j, i);
//				flag = 0;
//				break;
//			}
//		}
//		else
//		{
//			break;
//		}
//	}         //���������ĵ�max2
//	*/	//����Խ��
//	
//	
//	//����ߵ�����꣬���ҵ������������
//	circle(imageROI2, Point(max1.x, max2.y), 15, Scalar(225, 225, 0), -1);
//	circle(g_srcImage, Point(max1.x, matchLocation.y), 15, Scalar(225, 225, 0), -1);
//	namedWindow("11", WINDOW_KEEPRATIO);
//	imshow("11", imageROI2);
//	namedWindow("12", WINDOW_KEEPRATIO);
//	imshow("12", g_srcImage);
//	//�������ĵ��������Ҫ���ľ���
//	double distance;
//	double x1 = matchLocation.x + g_templateImage.cols / 2, y1 = matchLocation.y + g_templateImage.rows;
//	double x2 = max1.x, y2 = max2.y;
//	distance = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
//	cout << "��һ��Ҫ�������ؾ���:" << distance << endl;
//
//	waitKey();	
//	return 0;
//}