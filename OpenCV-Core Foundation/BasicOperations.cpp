#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void basicOperations() {
	//reading or loading an image Mat img = imread(filename);
	Mat img = imread("./assests/basket.jpg", IMREAD_GRAYSCALE);

	
	/*Format of the file is determined by its content (first few bytes). To save an image to a file:
 imwrite(filename, img);

 //accessing pixel intensity
 Scalar inten


*/


}