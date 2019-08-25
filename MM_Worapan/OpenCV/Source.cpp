#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

/*
* 1. FUNCTION TO FIND M, K MATRIX IN VERTICAL DIRECTION
*		1.1. Perform padding with duplicate. Use opencv function copyMakeBorder().
*		1.2. Calculate energy matrix cL, cU, cR
*		1.3. Calculate M matrix
*		1.4. Calculate K matrix
* 2. FUNCTION TO FIND BEST SEAM IN VERTICAL DIRECTION
*		2.1. Use vector<int> to store best seam (Vector is like an arraylist. It can expand dynamically)
* 3. FUNCTION TO FIND M, K MATRIX IN HORIZONTAL DIRECTION
*		3.1. Perform padding with duplicate. Use opencv function copyMakeBorder().
*		3.2. Calculate energy matrix cL, cU, cR
*		3.3. Calculate M matrix
*		3.4. Calculate K matrix
* 4. FUNCTION TO FIND BEST SEAM IN HORIZONTAL DIRECTION
*		4.1. Use vector<int> to store best seam (Vector is like an arraylist. It can expand dynamically)
* 5. FUNCTION TO INSERT/ DELETE BEST SEAM VERTICALLY AND HORIZONTALLY
*/

int main() {
	//Display an Image
	Mat img = imread("fond.JPG", IMREAD_COLOR);
	namedWindow("Actual", WINDOW_AUTOSIZE);
	//namedWindow("M_matrix", WINDOW_AUTOSIZE);
	//namedWindow("Best seam", WINDOW_AUTOSIZE);

	imshow("Actual", img);
	int c = cvWaitKey(0);

	Size sz = img.size();
	int height = sz.height;
	int width = sz.width;

	/*Vector for storing the best seam*/

	if (img.empty()) {
		return -1;
	}

	/*ESC = 27, a = 97, d = 100, s = 115, w = 119*/
	while (c != 27) {
		/*Looping till get the command 'a', 'd', 'w', 's'*/
		while (c != 97 && c != 100 && c!= 115 && c != 119 && c != 27) {
			c = cvWaitKey(0);
		}
		/*Keyboard command :: 'a' and 'd' => vertical best seam, 'w' and 's' horizontal best seam
		'a' => Reduce width, 'd' => increase width*/

		vector<int> bestSeam;

		if (c == 97 || c == 100) {

			/*Construct M matrix and K matrix in the vertical direction*/
			Mat paddedImage;
			Mat grayImage;
			
			/*Convert Image to grayscale*/
			cvtColor(img, grayImage, COLOR_BGR2GRAY);
			Mat M_matrix(Size(width, height), CV_8UC1, Scalar(0));
			Mat K_matrix(Size(width, height), CV_8UC1, Scalar(0));

			/*Perform padding with duplicate using openCV function*/
			copyMakeBorder(grayImage, paddedImage, 1, 1, 1, 1, BORDER_REPLICATE);

			int r_M, c_M;
			int cL, cU, cR;
			int mL, mU, mR;
			int min_M;

			/*Start from 1 - i-i because the image is padded*/
			for (int i = 1; i < paddedImage.rows - 1; i++) {
				for (int j = 1; j < paddedImage.cols - 1; j++) {
					/*Change coordinate in padded image to coordinate in M and K matrix*/
					r_M = i - 1;
					c_M = j - 1;

					/*Calculate forward energy*/
					cL = abs((int)paddedImage.at<uchar>(i, j + 1) - (int)paddedImage.at<uchar>(i, j - 1)) + abs((int)paddedImage.at<uchar>(i - 1, j) - (int)paddedImage.at<uchar>(i, j - 1));
					cU = abs((int)paddedImage.at<uchar>(i, j + 1) - (int)paddedImage.at<uchar>(i, j - 1));
					cR = abs((int)paddedImage.at<uchar>(i, j + 1) - (int)paddedImage.at<uchar>(i, j - 1)) + abs((int)paddedImage.at<uchar>(i - 1, j) - (int)paddedImage.at<uchar>(i, j + 1));

					/*Finding Left M, Upper M, and Right M*/
					if (c_M == 0 || r_M == 0) {
						mL = cL;
					}
					else {
						mL = ((int)M_matrix.at<uchar>(r_M - 1, c_M - 1) + cL);
					}
					if (r_M == 0) {
						mU = cU;
					}
					else {
						mU = ((int)M_matrix.at<uchar>(r_M - 1, c_M) + cU);
					}
					if (c_M >= width - 1 || r_M == 0) {
						mR = cR;
					}
					else {
						mR = ((int)M_matrix.at<uchar>(r_M - 1, c_M + 1) + cR);
					}

					// Ternary operator approach
					// mL = ((c_M == 0 || r_M == 0) ? cL : ((int)M_matrix.at<uchar>(r_M - 1, c_M - 1) + cL));
					// mU = ((r_M == 0) ? cU : ((int)M_matrix.at<uchar>(r_M - 1, c_M) + cU));
					// mR = ((c_M >= width -1 || r_M == 0) ? cR : ((int)M_matrix.at<uchar>(r_M - 1, c_M + 1) + cR));

					/*Assign value to the M matrix*/
					min_M = min(mL, min(mU, mR));
					M_matrix.at<uchar>(r_M, c_M) = min(mL, min(mU, mR));

					/*Find offset and assign to K matrix*/
					if (r_M == 0) {
						K_matrix.at<uchar>(r_M, c_M) = 0;
					}
					else {
						if ((c_M != 0) && (mL == min(mL, min(mU, mR)))) {
							K_matrix.at<uchar>(r_M, c_M) = 1;
						}
						else if (mU == min(mL, min(mU, mR))) {
							K_matrix.at<uchar>(r_M, c_M) = 2;
						}
						else {
							if (c_M >= width - 1) {
								K_matrix.at<uchar>(r_M, c_M) = 2;
							}
							else {
								K_matrix.at<uchar>(r_M, c_M) = 3;
							}
						}
					}
				}
			}

			//cvWaitKey(1);
			//imshow("M_matrix", M_matrix);

			/*Find the best seam in vertical direction*/
			
			/*Create a matrix for showing the best seam*/
			Mat seam_matrix(Size(width, height), CV_8UC1, Scalar(0));

			/*Finding the least value in the bottom row of M matrix*/
			int seam_column = 0;
			for (int i = 0; i < width; i++) {
				if ((int)M_matrix.at<uchar>(height - 1, i) < (int)M_matrix.at<uchar>(height - 1, seam_column)) {
					seam_column = i;
				}
			}

			/*Building the best seam and insert it into the matrix*/
			seam_matrix.at<uchar>(height - 1, seam_column) = 255;
			bestSeam.push_back(seam_column);						/*push_back is like ArrayList.add()*/
			int seam_column_new;
			for (int i = height - 1; i > 0; i--) {
				//cout << seam_column << endl;
				seam_column_new = seam_column + K_matrix.at<uchar>(i, seam_column) - 2;
				//cout << i << " " << seam_column_new << " + " << (int)K_matrix.at<uchar>(i, seam_column) << endl;
				seam_matrix.at<uchar>(i - 1, seam_column_new) = 255;
				bestSeam.push_back(seam_column_new);
				seam_column = seam_column_new;
			}

			//cvWaitKey(1);
			//imshow("Best seam", seam_matrix);
		}

		/*'w' = > increase height, 's' = > reduce height*/
		if (c == 115 || c == 119) {
			/*Construct M matrix and K matrix in the horizontal direction*/
			//CODE HERE

			/*Find the best seam in horizontal direction*/
			//CODE HERE
		}
		if (c == 97) {
			// Reduce width or delete seam vertically
			// Copy the pixels into this image
			Mat img_new(height, --width, CV_8UC3, Scalar(0, 0, 0));
			//CODE HERE

			Mat dummy(1, 1, CV_8UC3, Vec3b(0, 0, 0));
			for (int i = 0; i < height; i++) {

				// segment the image into 2 parts. To the left of the seam and to the right of the seam.
				Mat new_row;
				Mat left = img.rowRange(i, i + 1).colRange(0, bestSeam[i]);
				Mat right = img.rowRange(i, i + 1).colRange(bestSeam[i] + 1, width);

				// Merge the two segments
				if (!left.empty() && !right.empty()) {
					hconcat(left, right, new_row);
					hconcat(new_row, dummy, new_row);
				}
				else {
					if (left.empty()) {
						hconcat(right, dummy, new_row);
					}
					else if (right.empty()) {
						hconcat(left, dummy, new_row);
					}
				}
				//insert new row into img_new
				new_row.copyTo(img_new.row(i));
			}

			// Show the resized image
			imshow("Actual", img_new);
			// Clone img_new into img for the next loop processing
			img.release();
			img = img_new.clone();
			img_new.release();
		}
		if (c == 100) {
			// Increase width or insert seam vertically
			// Copy the pixels into this image
			Mat img_new(height, ++width, CV_8UC3, Scalar(0, 0, 0));
			//CODE HERE

			// Show the resized image
			imshow("Actual", img_new);
			// Clone img_new into img for the next loop processing
			img.release();
			img = img_new.clone();
			img_new.release();
		}
		if (c == 115) {
			// Reduce height or delete seam horizontally
			// Copy the pixels into this image
			Mat img_new(--height, width, CV_64FC3, Scalar(0, 0, 0));
			//CODE HERE

			// Show the resized image
			imshow("Actual", img_new);
			// Clone img_new into img for the next loop processing
			img.release();
			img = img_new.clone();
			img_new.release();
		}
		if (c == 119) {
			// Increase height or insert seam horizontally
			// Copy the pixels into this image
			Mat img_new(--height, width, CV_64FC3, Scalar(0, 0, 0));
			//CODE HERE

			// Show the resized image
			imshow("Actual", img_new);
			// Clone img_new into img for the next loop processing
			img.release();
			img = img_new.clone();
			img_new.release();
		}

		if (c == 27) break;

		c = cvWaitKey(0);
	}
	return 0;
}
