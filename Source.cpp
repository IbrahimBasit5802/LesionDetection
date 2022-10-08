#include <iostream>

#include <opencv2/core.hpp>

#include <opencv2/imgcodecs.hpp>

#include <opencv2/highgui.hpp>

#include <stdlib.h>
#include "Task01.h"

#include "Task02.h"
#include "Task03.h"

#include "Task04.h"


using namespace cv;
using namespace std;





int main() {
	Mat img = imread("./OriginalImages/IMD091.bmp", IMREAD_GRAYSCALE);
	imshow("img", img);

	system("CLS");

	cout << "Applying K-Mean..." << endl << endl;

	img = kMean(img);

	cout << "K-Mean done." << endl;
	cout << endl;
	cout << "Applying Connected Component Labeling..." << endl << endl;
	img = conectedComponentLabeling(img);
	cout << "Connected Components Done." << endl;

	// calculate dice coefficiant for connected component labeling:
	cout << endl;
	Mat img2 = imread("./GroundTruths/IMD091_lesion.bmp", IMREAD_GRAYSCALE);

	cout << "Dice Coefficiant after applying K-Mean and Connected Component Labeling Respectively: " << calculateDice(img2, img) << endl;




	cv::imwrite("work_pls2.bmp", img);

	cout << endl;

	cout << "RLC Values: " << endl << endl;

	// computes RLC and prints the values: 
	computeRLC(img);






	cv::waitKey(0);
	cv::destroyAllWindows();



	return 0;

}
