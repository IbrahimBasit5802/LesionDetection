#pragma once

#include <iostream>

#include <opencv2/core.hpp>

#include <opencv2/imgcodecs.hpp>

#include <opencv2/highgui.hpp>


using namespace cv;
using namespace std;


double calculateDice(Mat ground_truth, Mat output) {


	int** img_arr = new  int* [output.rows];

	for (int i = 0; i < output.rows; i++) {
		img_arr[i] = new  int[output.cols];
	}

	for (int i = 0; i < output.rows; i++) {
		for (int j = 0; j < output.cols; j++) {
			img_arr[i][j] = int(output.at<uint8_t>(i, j));
		}
	}

	int** gt_arr = new  int* [ground_truth.rows];

	for (int i = 0; i < ground_truth.rows; i++) {
		gt_arr[i] = new int[ground_truth.cols];
	}

	for (int i = 0; i < ground_truth.rows; i++) {
		for (int j = 0; j < ground_truth.cols; j++) {
			gt_arr[i][j] = int(ground_truth.at<uint8_t>(i, j));
		}
	}

	int TP = 0;

	int FP = 0;
	int FN = 0;
	for (int i = 0; i < output.rows; i++) {
		for (int j = 0; j < output.cols; j++) {
			

			if (gt_arr[i][j] == 255) {
				TP++;
			}
			if (gt_arr[i][j] == 0 && img_arr[i][j] == 255) {
				FP++;
			}

			if (gt_arr[i][j] == 255 && img_arr[i][j] == 0) {
				FN++;
			}

		}
	}




	for (int i = 0; i < output.rows; i++) {
		delete[] img_arr[i];
	}

	delete[] img_arr;

	for (int i = 0; i < ground_truth.rows; i++) {
		delete[] gt_arr[i];
	}

	delete[] gt_arr;

	double dice_coeff = (double(2) * double(TP)) / (double(FN) + (double(2) * double(TP)) + double(FP));

	return dice_coeff;


}