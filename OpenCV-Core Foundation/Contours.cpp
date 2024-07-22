
/*
Finding contours in a image has following steps

Read the Input Image: Load an image from a file.
Convert to Grayscale: Convert the image to grayscale.
Blur the Image: Apply a blur to the grayscale image to reduce noise.
Edge Detection: Use the Canny edge detection algorithm to find edges in the image.
Find Contours: Identify contours based on the edges detected by the Canny algorithm.
Draw Contours: Draw the identified contours on a new image.
Display Images: Show the original image and the image with drawn contours.


RETR_TREE:

Purpose: It’s like looking at the full family tree of neighborhoods. It helps you see not just the main neighborhoods but also any smaller neighborhoods within them and how they are all related.
How it works: When you use RETR_TREE, OpenCV finds all the contours and organizes them into a tree structure:
Parent contours: Larger contours that may contain smaller ones inside them.
Child contours: Smaller contours inside larger ones.
Sibling contours: Contours that are on the same level (e.g., multiple neighborhoods in the same city).
Example:

If you have an image with several shapes:

RETR_TREE will tell you if one shape is inside another and how the shapes are organized.
CHAIN_APPROX_SIMPLE (Contour Approximation Method)
What it does:

Think of tracing the outline of a complex shape with a pen. If you draw every tiny detail, you’ll end up with a very detailed and long trace. But if you only trace the important corners and turns, you get a simpler and shorter trace that still outlines the shape accurately.

In the context of contours:

Contours: Outlines of shapes or objects in an image.
Approximation: Simplifying the contour to make it easier to work with.
CHAIN_APPROX_SIMPLE:

Purpose: It’s like simplifying your detailed outline by only keeping the essential points that define the shape’s boundary.
How it works: Instead of keeping every single point along the contour, this method compresses the contour by removing points that don’t change the overall shape significantly. It keeps only the points where the contour changes direction or has significant features.


RETR_EXTERNAL: Only outermost contours.
RETR_LIST: All contours without hierarchy.
RETR_CCOMP: All contours with a two-level hierarchy (outer and nested).
RETR_TREE: All contours with a full hierarchical tree.


The 0 indicates that all levels of contours are drawn, meaning it will include the current contour and all its nested contours.
If you only wanted to draw the outermost contours and not any nested ones, you might use 0 or another value depending on your needs.
*/
#include "Contours.h"


int thresh = 100;
Mat src_gray;
RNG rng(12345);
void thresh_callback(int, void*);
void Contours() {

	Mat src = imread("./assets/basket.jpg");
	
	//convert image to grayscale
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	//blur 
	blur(src_gray, src_gray, Size(3, 3));

	const char* source_window = "Source";
	namedWindow(source_window);
	imshow(source_window, src);


	const int max_thresh = 255;
	createTrackbar("Canny thresh", source_window, &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	waitKey();
	return;
}



void thresh_callback(int, void*) {
	Mat canny_output;
	Canny(src_gray, canny_output, thresh, thresh * 2);

	//find the contours in edge detected image
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);

	//drawing contours
	for (size_t i = 0; i < contours.size(); i++) {
		//randomly generate a color for each contor
		Scalar color= Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
	}
	imshow("Contours", drawing);
}