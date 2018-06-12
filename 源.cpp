//#include<iostream>
//#include<opencv2\opencv.hpp>
//using namespace cv;
//using namespace std;
//
////定义全局变量
//Mat g_srcImage,srcImage,g_templateImage,g_resultImage;
//
//
//int main()
//{
//	//读入游戏截图和目标模板
//	g_srcImage = imread("1.png", 1);
//	g_templateImage = imread("template.jpg", 1);
//	namedWindow("0", WINDOW_KEEPRATIO);                                  //如果不用namedwindow直接autosize则不可调节大小，显示不完整
//	namedWindow("1", WINDOW_KEEPRATIO);
//	imshow("0", g_srcImage);
//	imshow("1", g_templateImage);
//	//存储原游戏截图
//	g_srcImage.copyTo(srcImage);                                         //需在g_srcimage载入图片后复制
//	//初始化用于结果输出的矩阵
//	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
//	int resultImage_cols = g_srcImage.rows - g_templateImage.cols + 1;
//	g_resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1);
//	//用matchTemplate函数进行匹配
//	matchTemplate(g_srcImage, g_templateImage, g_resultImage, TM_SQDIFF);//有6种匹配方法
//	namedWindow("2", WINDOW_KEEPRATIO);
//	imshow("2", g_resultImage);
//	//标准化
//	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());
//	namedWindow("3", WINDOW_KEEPRATIO);
//	imshow("3", g_resultImage);
//	//通过函数minMaxLoc定位最匹配的位置
//	double minValue, maxValue ;
//	Point minLocation, maxLocation;
//	Point matchLocation;
//	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());   //Mat()表示不用掩膜
//	matchLocation = minLocation;                  //SQDIFF越小的数值有更高的匹配结果 ；matchlocation是g_template矩形左上角点
//	//绘制矩形
//	rectangle(g_srcImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), Scalar(0, 0, 225), 5);
//	rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), Scalar(0, 0, 225), 5);  //最后一项参数为thickness
//	//显示匹配结果
//	namedWindow("4", WINDOW_KEEPRATIO);
//	namedWindow("5", WINDOW_KEEPRATIO);
//	imshow("4", g_srcImage);
//	imshow("5", g_resultImage);
//	//标记小人所在墩的点
//	circle(g_srcImage, Point(matchLocation.x + g_templateImage.cols/2, matchLocation.y + g_templateImage.rows), 15, Scalar(225,225,0),-1);   //radius，color，thickness，设为负数即实心圆 ；由左上角的点至底边中点的坐标变换
//	namedWindow("6", WINDOW_KEEPRATIO);
//	imshow("6", g_srcImage);
//	
//	
//
//	
//	//转灰度图降噪边缘检测
//	Mat gray;
//	cvtColor(srcImage, gray, COLOR_BGR2GRAY);
//	GaussianBlur(gray, gray, Size(3, 3),5);
//	Canny(gray,gray , 3, 9);        //高低滞后性阈值
//	namedWindow("7", WINDOW_KEEPRATIO);
//	imshow("7", gray);
//	//将小人所在区域设为黑色
//	Mat imageROI1;
//	imageROI1 = gray(Rect(matchLocation.x, matchLocation.y, g_templateImage.cols, g_templateImage.rows));
//	imageROI1 = { Scalar(0,0,0) };
//	namedWindow("8", WINDOW_KEEPRATIO);
//	imshow("8", gray);
//	//裁剪出目标区域，避免干扰
//	Mat imageROI2;
//	imageROI2 = gray(Rect( 0,450 ,srcImage.cols,matchLocation.y-300));           //rows行，cols列；矩形左上角坐标，矩形长、宽,宽度应以小人为参考才具有普适性
//	namedWindow("9", WINDOW_KEEPRATIO);
//	imshow("9", imageROI2);
//
////	cout << (int)srcImage.at<uchar>(90,90) << "33" << endl;      //必须要加上int类型的强制转换
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
//	}          //纵坐标最小的点max1
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
//	/*//遍历像素找像素值为255中纵坐标最小和横坐标最大的点
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
//	}          //纵坐标最小的点max1
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
//	}         //横坐标最大的点max2
//	*/	//坐标越界
//	
//	
//	//以最高点横坐标，最右点纵坐标作落点
//	circle(imageROI2, Point(max1.x, max2.y), 15, Scalar(225, 225, 0), -1);
//	circle(g_srcImage, Point(max1.x, matchLocation.y), 15, Scalar(225, 225, 0), -1);
//	namedWindow("11", WINDOW_KEEPRATIO);
//	imshow("11", imageROI2);
//	namedWindow("12", WINDOW_KEEPRATIO);
//	imshow("12", g_srcImage);
//	//由两中心点坐标计算要跳的距离
//	double distance;
//	double x1 = matchLocation.x + g_templateImage.cols / 2, y1 = matchLocation.y + g_templateImage.rows;
//	double x2 = max1.x, y2 = max2.y;
//	distance = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
//	cout << "下一步要跳的像素距离:" << distance << endl;
//
//	waitKey();	
//	return 0;
//}