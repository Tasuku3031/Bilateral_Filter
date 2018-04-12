#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

int main(void) {
	Mat img = imread("nana.jpg");
	if (img.empty()) {
		std::cout << " not found" << std::endl;
		return -1;
	}

	int k;
	double z1, z2;
	std::cout << "配列の数を入力してください" << std::endl;
	std::cin >> k;
	std::cout << "距離の標準偏差の値を入力してください" << std::endl;
	std::cin >> z1;
	std::cout << "輝度差の標準偏差の値を入力してください" << std::endl;
	std::cin >> z2;

	Mat dst = Mat::zeros(img.rows, img.cols, CV_8UC3);

	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {

			double b = 0, g = 0, r = 0;
			double sumb = 0, sumg = 0, sumr = 0;
			Vec3b tmp2 = img.at<Vec3b>(y, x);

			for (int i = (k - 1) / 2; i < ((k - 1) / 2) + k; i++) {
				for (int j = (k - 1) / 2; j < ((k - 1) / 2) + k; j++) {
					int s = y + (i - (k + 1) / 2);
					int t = x + (j - (k + 1) / 2);
					if (s < 0) {
						s = 0;
					}
					if (s >= img.rows) {
						s = img.rows - 1;
					}
					if (t < 0) {
						t = 0;
					}
					if (t >= img.cols) {
						t = img.cols - 1;
					}

					Vec3b tmp1 = img.at<Vec3b>(s, t);

					int m = i - (k + 1) / 2;
					int n = j - (k + 1) / 2;
					double fb = (exp(-(n * n + m * m) / (2 * z1 * z1))) * (exp(-(tmp1[0] - tmp2[0]) * (tmp1[0] - tmp2[0]) / (2 * z2 * z2)));
					double fg = (exp(-(n * n + m * m) / (2 * z1 * z1))) * (exp(-(tmp1[1] - tmp2[1]) * (tmp1[1] - tmp2[1]) / (2 * z2 * z2)));
					double fr = (exp(-(n * n + m * m) / (2 * z1 * z1))) * (exp(-(tmp1[2] - tmp2[2]) * (tmp1[2] - tmp2[2]) / (2 * z2 * z2)));
					b += tmp1[0] * fb;
					g += tmp1[1] * fg;
					r += tmp1[2] * fr;

					sumb += fb;
					sumg += fg;
					sumr += fr;
				}
			}
			b = b / sumb;
			g = g / sumg;
			r = r / sumr;
			dst.at<Vec3b>(y, x) = Vec3b(b, g, r);
		}
	}

	imshow("View", img);
	imshow("Filter", dst);
	imwrite("nana2.jpg", dst);
	waitKey(0);

	return 0;
}