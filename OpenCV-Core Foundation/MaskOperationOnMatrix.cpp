/*Mask operations on matrices are quite simple. 
The idea is that we recalculate each pixel's value in an image according to a mask matrix (also known as kernel). This mask holds values that will adjust how much influence neighboring pixels (and the current pixel) have on the new pixel value. From a mathematical point of view we make a weighted average,
with our specified values.*/
/*This technique is often used for tasks like blurring, sharpening, edge detection, and contrast enhancement.
The mask contains values that define how the pixel values in the image should be combined to produce new pixel values.

*/

/*lets say the mask formula is 
I(i,j)=5*I(i,j) - [ I(i-1,j) + I(i+1,j) + I(i,j-1) + I(i,j+1) ]
we can write this in form matrix known as mask matrix or kernel matrix as follows
 	
   [ 0 -1 0
    -1 5 -1
    0 -1 0 ]

    check the convolution matrix tutorial for how filtering actually works

*/
/*.depth() Function:

When called on a Mat object, .depth() returns an integer that corresponds to the data type of the matrix elements.
The integer values typically correspond to predefined constants in OpenCV, such as CV_8U, CV_32F, etc.
Common Depth Values:

CV_8U: 8-bit unsigned integers (0 to 255).
CV_8S: 8-bit signed integers (-128 to 127).
CV_16U: 16-bit unsigned integers (0 to 65535).
CV_16S: 16-bit signed integers (-32768 to 32767).
CV_32S: 32-bit signed integers.
CV_32F: 32-bit floating point.
CV_64F: 64-bit floating point.
*/


#include "MaskOperationOnMatrix.h"
Mat& maskUsingFilter2D(Mat& A) {
    /*This syntax (<<) is used in OpenCV to initialize matrix elements row by row. In this line, it initializes the first row of the 3x3 matrix with the values 0, -1, 0.
*/
    Mat kernel = (Mat_<char>(3, 3) << 1, 0, -1,
        1, 0, -1,
        1, 0, -1);
    Mat resultF;
    filter2D(A, resultF, A.depth(), kernel);
    imshow("Masked or filtered image is ", resultF);
    waitKey(0);
    return resultF;

}