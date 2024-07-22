//opencv Mat data type

//Mat the basic container

//Creating Mat Object explicitly"
//8UC3 -> 8 bit Unsigned character, 3 channels

/*
Data Type :

8U: 8 - bit unsigned integers(0 - 255).
8S : 8 - bit signed integers(-128 to 127).
16U : 16 - bit unsigned integers(0 - 65535).
16S : 16 - bit signed integers(-32768 to 32767).
32S : 32 - bit signed integers.
32F : 32 - bit floating - point numbers.
64F : 64 - bit floating - point numbers.

*/

#include <opencv2/opencv.hpp> 
#include<iostream>
#include "Itreating-through-Image.h"
#include "MaskOperationOnMatrix.h"
#include "TemplateMatching.h"
#include "Contours.h"
using namespace std;
using namespace cv;


int main() {

	//creating Mat explicitly using Mat constructor
	Mat M(2, 2, CV_16UC3, Scalar(0, 0,255));
	cout << M << endl << endl;

	Mat E = Mat::eye(4, 4, CV_64F);
	cout << endl << "E= " << endl << E << endl << endl;
	Mat O = Mat::ones(6, 6, CV_16U);
	cout << endl << "O= " << endl << O << endl << endl;
	Mat Z = Mat::zeros(3, 3, CV_8UC1);
	cout <<endl<< "Z = " << endl << " " << Z << endl << endl;


	//create headr part of Mat
	Mat A, C;
	A = imread("./assets/basket.jpg");
	//copy constructor
	Mat B(A);
	C = A;

	//cout << endl << "A = " << A << endl << endl;
	//all the above methods point to the same single data mtrix and making a 
	//modification using any of them will affect all the other one as well.


	//In case, if we want to create the copy of matrix itself too

	Mat F = A.clone();
	Mat G;
	A.copyTo(G);
	//cout << endl << "G = " << G << endl << endl;

	//If we want to refer to only asubsection of full data


	//Range of Interest 

	Mat X(A, Rect(0, 0, 10, 10));//x,y-10,10  width,height-100,100
	//cout << endl << "X = " << X << endl << endl;

	//we can also use row and column boudaries
	/*Range(0, 2) specifies the range of columns to be included in S.
	0: The starting column index (inclusive).
	2: The ending column index (exclusive).*/
	cout << "Number of rows in image : "<<A.rows<<endl;
	cout << "NUmber of columns in image are : " << A.cols << endl;
	Mat S = A(Range::all(), Range(0, 200));
	//cout << endl << "S = " << S << endl << endl;

	//Output ogother common points
	Point2f P2f(5, 1);
	Point3f P3f(2, 6, 7);

	cout << endl << P3f << endl;

	cout << endl;

	vector<int> v(10,0);
	cout << endl << "Vector " << endl;
	cout << Mat(v) << endl;


	//accessing the intensity of pixel in an image
	double intensity = E.at<double>(Point(1, 1));
	cout << "Intensity is " << intensity << endl;


	//accessing intensity value in case of BGR channel

	Vec3b listt = A.at<Vec3b>(Point(0, 0));
	uchar blue = listt[0];
	uchar green = listt[1];
	uchar red = listt[2];

	cout << "Number of channels in listt is " << A.channels() << endl;
	cout << "BGR " << (int)blue << " " << (int)green << " " << (int)red << endl;

	cout << endl << X << endl << endl;

	cout << "Mat type is " << E.type() << endl;
	//maskUsingFilter2D(A);
	//MatIm(A);
	//vector of points
	vector<Point2f> vPoints(20);
for (size_t i = 0; i < vPoints.size(); ++i)
		vPoints[i] = Point2f((float)(i * 5), (float)(i % 7));
	cout << "A vector of 2D Points = " << vPoints << endl << endl;


	//Creating a Histogram from image and normalizing it
	imshow("for Histogram", A);


	//separating planes in histogram
	vector<Mat> planes;
	split(A, planes);

	

	int histSize = 256;
	float range[] = {0,256};
	const float* histRange[] = { range };
	bool uniform = true;
	bool accumulate = false;
	Mat b_hist,g_hist,r_hist;
	calcHist(&planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate);
	calcHist(&planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate);
	calcHist(&planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate);


	int h_ww = 512;
	int h_hh = 400;
	int bin_w = cvRound((double)h_ww / histSize);

	Mat histImage(h_hh, h_ww, CV_8UC3, Scalar(0, 0, 0));


	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++) {
		line(histImage, Point(bin_w*(i-1),h_hh - cvRound(b_hist.at<float>(i-1))), Point(bin_w*(i),h_hh-cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), h_hh - cvRound(g_hist.at<float>(i - 1))), Point(bin_w * (i), h_hh - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), h_hh - cvRound(r_hist.at<float>(i - 1))), Point(bin_w * (i), h_hh - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);

	}

	imshow("Histogram is ", histImage);
	waitKey(0);
	templateMatching();
	Contours();

	



	//imshow("row and column",S);
	//waitKey(0);



}