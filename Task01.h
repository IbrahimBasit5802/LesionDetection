#pragma once
#include <iostream>

#include <opencv2/core.hpp>

#include <opencv2/imgcodecs.hpp>

#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;



void insertionSort(int array[], int size) {
	for (int step = 1; step < size; step++) {
		int key = array[step];
		int j = step - 1;
		while (key < array[j] && j >= 0) {
			array[j + 1] = array[j];
			--j;
		}
		array[j + 1] = key;
	}
}

int removeDuplicates(int arr[], int n)
{
	if (n == 0 || n == 1) {
		return n;
	}
		
	int* temp = new int[n];

	int x = 0;
	
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] != arr[i + 1]) {
			temp[x++] = arr[i];
		}
			
	}

	temp[x++] = arr[n - 1];

	for (int i = 0; i < x; i++) {
		arr[i] = temp[i];
	}
		

	delete[] temp;

	return x;
}


Mat conectedComponentLabeling(Mat img) {
	int** img_arr = new  int* [img.rows];

	for (int i = 0; i < img.rows; i++) {
		img_arr[i] = new  int[img.cols];
	}

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			img_arr[i][j] = int(img.at<uint8_t>(i, j));
		}
	}

	int x1, x2, x3, x4;
	// set borders to black assuming all pics's have largest lesion is not in the borders 
	for (int i = 0; i < img.cols; i++)
	{
		img_arr[0][i] = 0;
		img_arr[img.rows - 1][i] = 0;
	}

	for (int j = 0; j < img.rows; j++)
	{
		img_arr[j][0] = 0;
		img_arr[j][img.cols - 1] = 0;
	}


	
	int label_count = 1;
	// Parallel Equivalence Arrays:
	int* arr1 = new int[100000];
	int* arr2 = new int[100000];
	int s = 0;
	// Labeling:

	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{

			x1 = img_arr[i][j - 1];

			x2 = img_arr[i - 1][j - 1];
			
			x3 = img_arr[i - 1][j];

			x4 = img_arr[i - 1][j + 1];

			if (img_arr[i][j] != 0)
			{
				// 0000
				if (x1 == 0 && x2 == 0 && x3 == 0 && x4 == 0)
				{
					img_arr[i][j] = label_count++;
				}


				//1000
				else if (x1 != 0 && x2 == 0 && x3 == 0 && x4 == 0)
				{
					img_arr[i][j] = x1;

				}
				//0100
				else if (x1 == 0 && x2 != 0 && x3 == 0 && x4 == 0)
				{
					img_arr[i][j] = x2;
				}
				//0010
				else if (x1 == 0 && x2 == 0 && x3 != 0 && x4 == 0)
				{
					img_arr[i][j] = x3;
				}
				//0001
				else if (x1 == 0 && x2 == 0 && x3 == 0 && x4 != 0)
				{
					img_arr[i][j] = x4;
				}


				// 0011
				else if (x1 == 0 && x2 == 0 && x3 != 0 && x4 != 0)
				{
					if (x3 == x4)
					{
						img_arr[i][j] = x3;
					}
					else
					{

						img_arr[i][j] = min(x3, x4);
						arr2[s] = min(x3, x4);
						arr1[s] = max(x3, x4);
						s++;
					}
				}
				// 0101
				else if (x1 == 0 && x2 != 0 && x3 == 0 && x4 != 0)
				{
					if (x2 == x4)
					{
						img_arr[i][j] = x4;
					}
					else
					{
						img_arr[i][j] = min(x2, x4);
						arr2[s] = min(x2, x4);
						arr1[s] = max(x2, x4);
						s++;

					}
				}
				// 0110
				else if (x1 == 0 && x2 != 0 && x3 != 0 && x4 == 0)
				{
					if (x3 == x2)
					{
						img_arr[i][j] = x2;
					}
					else
					{

						img_arr[i][j] = min(x2, x3);
						arr2[s] = min(x2, x3);
						arr1[s] = max(x2, x3);
						s++;

					}
				}
				// 1001
				else if (x1 != 0 && x2 == 0 && x3 == 0 && x4 != 0)
				{
					if (x1 == x4)
					{
						img_arr[i][j] = x4;
					}
					else
					{

						img_arr[i][j] = min(x1, x4);
						arr2[s] = min(x1, x4);
						arr1[s] = max(x1, x4);
						s++;

					}
				}
				// 1010
				else if (x1 != 0 && x2 == 0 && x3 != 0 && x4 == 0)
				{
					if (x1 == x3)
					{
						img_arr[i][j] = x3;
					}
					else
					{

						img_arr[i][j] = min(x1, x3);
						arr2[s] = min(x1, x3);
						arr1[s] = max(x1, x3);
						s++;

					}
				}
				// 1100
				else if (x1 != 0 && x2 != 0 && x3 == 0 && x4 == 0)
				{
					if (x1 == x2)
					{
						img_arr[i][j] = x2;
					}
					else
					{

						img_arr[i][j] = min(x1, x2);
						arr2[s] = min(x1, x2);
						arr1[s] = max(x1, x2);
						s++;

					}
				}
				// 0111
				else if (x1 == 0 && x2 != 0 && x3 != 0 && x4 != 0)
				{
					if (x2 == x3 && x2 == x4)
					{
						img_arr[i][j] = x2;
					}
					else
					{
						int temparr[3];
						temparr[0] = x2;
						temparr[1] = x3;
						temparr[2] = x4;
						insertionSort(temparr, 3);
						img_arr[i][j] = temparr[0];
						int size = removeDuplicates(temparr, 3);



						for (int i = 0; i < size; i++)
						{
							arr2[s] = temparr[0];
							arr1[s] = temparr[i];
							s++;
						}
					}
				}
				// 1011
				else if (x1 != 0 && x2 == 0 && x3 != 0 && x4 != 0)
				{
					if (x1 == x3 && x1 == x4)
					{
						img_arr[i][j] = x1;
					}
					else
					{
						int temparr[3];
						temparr[0] = x1;
						temparr[1] = x3;
						temparr[2] = x4;
						insertionSort(temparr, 3);
						img_arr[i][j] = temparr[0];
						int size = removeDuplicates(temparr, 3);



						for (int i = 0; i < size; i++)
						{
							arr2[s] = temparr[0];
							arr1[s] = temparr[i];
							s++;
						}
					}
				}
				// 1101
				else if (x1 != 0 && x2 != 0 && x3 == 0 && x4 != 0)
				{
					if (x1 == x2 && x1 == x4)
					{
						img_arr[i][j] = x1;
					}
					else
					{
						int temparr[3];
						temparr[0] = x1;
						temparr[1] = x2;
						temparr[2] = x4;
						insertionSort(temparr, 3);
						img_arr[i][j] = temparr[0];
						int size = removeDuplicates(temparr, 3);



						for (int i = 0; i < size; i++)
						{
							arr2[s] = temparr[0];
							arr1[s] = temparr[i];
							s++;
						}
					}
				} 
				//1110
				else if (x1 != 0 && x2 != 0 && x3 != 0 && x4 == 0)
				{
					if (x1 == x2 && x1 == x3)
					{
						img_arr[i][j] = x1;
					}
					else
					{
						int temparr[3];
						temparr[0] = x1;
						temparr[1] = x2;
						temparr[2] = x3;
						insertionSort(temparr, 3);
						img_arr[i][j] = temparr[0];
						int size = removeDuplicates(temparr, 3);



						for (int i = 0; i < size; i++)
						{
							arr2[s] = temparr[0];
							arr1[s] = temparr[i];
							s++;
						}
					}
				} 
				// 1111
				else if (x1 != 0 && x2 != 0 && x3 != 0 && x4 != 0)
				{
					if (x1 == x2 && x1 == x3 && x1 == x4)
					{
						img_arr[i][j] = x1;
					}
					else
					{
						int temparr[4];
						temparr[0] = x1;
						temparr[1] = x2;
						temparr[2] = x3;
						temparr[3] = x4;
						insertionSort(temparr, 4);
						img_arr[i][j] = temparr[0];
						int size = removeDuplicates(temparr, 4);



						for (int i = 0; i < size; i++)
						{
							arr2[s] = temparr[0];
							arr1[s] = temparr[i];
							s++;
						}
					}
				} 
				
			}
		}
	}



	// Replace equivalences with same label:
	for (int i = 1; i < img.rows - 1; i++) {

		for (int j = 1; j < img.cols - 1; j++) {

			for (int x = s; x >= 0; x--) {

				if (img_arr[i][j] == arr1[x]) {

					img_arr[i][j] = arr2[x];

				}

			}

		}

	}




	delete[]  arr1;
	delete[] arr2;



	// Detect which label occur the most:

	// label_count = number of labels

	int* labels = new int[label_count];

	for (int i = 0; i < label_count; i++) {
		labels[i] = i + 1;
	}

	int* label_occurences = new int[label_count];

	for (int i = 0; i < label_count; i++) {
		label_occurences[i] = 0;
	}

	int num = 0;
	for (int x = 0; x < label_count; x++) {
		for (int i = 1; i < img.rows - 1; i++) {
			for (int j = 1; j < img.cols - 1; j++) {
				if (img_arr[i][j] == labels[x]) {
					label_occurences[x]++;
				}
			}
		}
	}

	// check max value in label_occurence

	int max = label_occurences[0];
	int max_index = 0;
	for (int i = 0; i < label_count; i++) {
		if (max < label_occurences[i]) {
			max = label_occurences[i];
			max_index = i;
		}
	}

	delete[] labels;
	delete[] label_occurences;

	for (int i = 1; i < img.rows - 1; i++) {
		for (int j = 1; j < img.cols - 1; j++) {
			if (img_arr[i][j] == max_index + 1) {
				img_arr[i][j] = 255;
			}

			else {
				img_arr[i][j] = 0;
			}


		}
	}

	for (int i = 0; i < img.rows; i++) {

		for (int j = 0; j < img.cols; j++) {

			img.at<uint8_t>(i, j) = img_arr[i][j];

		}

	}
	
	for (int i = 0; i < img.rows; i++) {
		delete[] img_arr[i];
	}

	delete[] img_arr;

	return img;
}