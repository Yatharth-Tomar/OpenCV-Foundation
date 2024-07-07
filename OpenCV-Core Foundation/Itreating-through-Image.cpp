#include "Itreating-through-Image.h"


/*When a function returns a reference, it means that instead of creating a copy of the object (Mat in this case), it operates directly on the original object passed to it.
This is efficient for large data structures like images because it avoids unnecessary copying.*/

Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table) {
	//checking some conditions
	CV_Assert(I.rows > 0 && I.cols > 0);
	//CV_Assert(I.depth() == CV_8UC3);


	const int channels = I.channels();

	/*cv::Mat
	Heterogeneous Data Types: cv::Mat can store matrices with various data types, which are not determined at compile time but rather at runtime.
	Explicit Type Specification: When you use iterators with cv::Mat, you need to specify the type explicitly to match the type of elements stored in the matrix. This is due to the flexible nature of cv::Mat,
	which can hold different types of data (e.g., uchar, float, Vec3b, etc.).*/

	switch (channels) {
	case 1: {
		//grayscale image
		MatIterator_<uchar> it, end;
		for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end;++it) {
			*it = table[*it];
		}
		break;
	}
	case 3: {
		MatIterator_<Vec3b> it, end;
		for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it) {
			(*it)[0] = table[(*it)[0]];//reducing blue channel
			(*it)[1] = table[(*it)[1]];//reducing green channel
			(*it)[2] = table[(*it)[2]];//reducing red channel
		}
		break;
	}
	}
	return I;
}

void MatIm(Mat A) {

	//reducing number of colors in an image to improve performance 
	//aslo known as color space reduction 

	/*Color space reduction- this program aims to reduce the number of color shades in an
	image , this is achieved by the dividing the existing color values of pixwls by a specified
	integer value, for example if a integer value is 10, every color value between 0 and 9 becomes 0,10
	to 19 becomes 10 and so on*/

	/*Look up Table - To speed up this color reduction process, the program uses
	a lookup table. This table is precomputed and maps each possible color value
	from 0 to 255 for unsigned char to its reduced value. Instead of performing a costly
	division operation for each pixel during image processin
	the program simply looks up the new value from this table*/


	if (A.empty()) {
		cerr << "Error:Image Cannot be Loaded " << endl;
		return;
	}

	//creating a lookup table

	int divideWith = 100;
	uchar table[256];
	
	cout << endl;
	for (int i = 0; i < 256; i++) {
		table[i] = (uchar)(divideWith * (i / divideWith));
	}
	cout << "Table is ";
	for (auto x : table) {
		cout << (int)x << " ";
	}
	Mat cc;
	A.copyTo(cc);
	ScanImageAndReduceIterator(A, table);
	imshow("original image is ", cc);
	imshow("Reduced image ", A);
	waitKey(0);








}