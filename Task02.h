#pragma once

#include <iostream>

#include <opencv2/core.hpp>

#include <opencv2/imgcodecs.hpp>

#include <opencv2/highgui.hpp>

#include "Math.h"

using namespace cv;
using namespace std;

double clusterMean(double **arr, int rows, int cols, int **arr2, int label) {
	double avg;
	double sum = 0;
	int count = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (arr2[i][j] == label) {
				sum += arr[i][j]; 
				count++;

			}
			

		}
	}

	avg = sum / count;

	return avg;
}


Mat kMean(Mat img) {

	double** img_arr = new double* [img.rows];
	int** parallel_arr = new int* [img.rows];

	for (int i = 0; i < img.rows; i++) {
		img_arr[i] = new double[img.cols];
		parallel_arr[i] = new int[img.cols];
	}

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			img_arr[i][j] = double(img.at<uchar>(i, j));
		}
	}

	int c1 = 31, c2 = 121;
	double d1, d2;



	for (int y = 0; y < 100; y++) {

		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				d1 = abs(c1 - img_arr[i][j]);
				d2 = abs(c2 - img_arr[i][j]);
				if (d1 < d2) {
					parallel_arr[i][j] = 1;
				}

				else {
					parallel_arr[i][j] = 2;
				}

			}
		}
		// update cluster centroids:

		c1 = clusterMean(img_arr, img.rows, img.cols, parallel_arr, 1);
		c2 = clusterMean(img_arr, img.rows, img.cols, parallel_arr, 2);
	}

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (parallel_arr[i][j] == 1) {
				parallel_arr[i][j] = 255;
			}
			else if (parallel_arr[i][j] == 2) {
				parallel_arr[i][j] = 0;
			}
		}
	}




	for (int i = 0; i < img.rows; i++) {

		for (int j = 0; j < img.cols; j++) {

			img.at<uchar>(i, j) = parallel_arr[i][j];

		}

	}






	for (int i = 0; i < img.rows; i++) {
		delete[] img_arr[i];
		delete[] parallel_arr[i];
	}
	delete[] img_arr;
	delete[] parallel_arr;
	

	return img;


}
