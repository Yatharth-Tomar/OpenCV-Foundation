#include "TemplateMatching.h"

const char* image_window = "Source Image";
const char* result_window = "Result window";
int match_method = 0;
int max_track = 5;


Mat base = imread("./assets/basket.jpg");
Mat tmp = imread("./assets/tmp.jpg");
Mat result;

void MatchingMethod(int, void*);

void templateMatching() {
	

	//check if images are empty or ot
	if (base.empty() or tmp.empty()) {
		cout << "Images not found !";
		return;
	}
	
	//creating name windows

	namedWindow(image_window ,WINDOW_AUTOSIZE);
	namedWindow(result_window, WINDOW_AUTOSIZE);

	////creating trackbar label

	const char* track_label= "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";

	//creating trackbar to select method for template matching
	createTrackbar(track_label, image_window,&match_method,max_track,MatchingMethod);

	//initialize template matching with the default method(0)
	MatchingMethod(0, 0);

	waitKey(0);



}

void MatchingMethod(int, void*) {
	Mat base_copy;
	base.copyTo(base_copy);

	//calculating the size of result image
	int rc = base.cols - tmp.cols + 1;
	int rr = base.rows - tmp.rows + 1;

	//create result matrix 
	result.create(rr, rc, CV_32FC1);

	//check if the selected methof accepts a mask based on method selection
	//bool method_accept_mask= (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED || match_method == TM_CCORR_NORMED);

	//Perform template matching
	matchTemplate(base,tmp,result,match_method);

	//normalizing the result to a range og 0 to 2 for better visualization
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());


	//we need variable to store the location of the best match
	double minVal, maxVal;
	Point minLoc, maxLoc;
	Point matchLoc;

	//find the best match location based on the method selected
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) {
		matchLoc = minLoc;
	}
	else {
		matchLoc = maxLoc;
	}

	//draw a rectangle around
	rectangle(base_copy, matchLoc, Point(matchLoc.x + tmp.cols, matchLoc.y + tmp.rows), Scalar::all(0), 2, 8, 0);
	rectangle(result, matchLoc, Point(matchLoc.x + tmp.cols, matchLoc.y + tmp.rows), Scalar::all(0), 2, 8, 0);

	imshow(image_window, base_copy);
	imshow(result_window, result);

}