// opencv_features_benchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Benchmark.h"
#include "Orb.h"
#include "Akaze.h"
#include "Brisk.h"
#include "ImageHandler.h"

int main()
{
	cv::ocl::setUseOpenCL(false);

	String path = "../opencv_features_benchmark/Images/";
	ImageHandler image_handler(path);
	vector<Mat> all_images = image_handler.get_images();

	cout << all_images.size() << endl;
	vector<Mat> image_subset(2);


	for (int idx = 0; idx < all_images.size(); idx++) {

		if ((idx + 1) == all_images.size()) {
			break;
		}

		cout << "Iteration: " << idx << "-" << (idx + 1) << endl;		

		image_subset[0] = all_images[idx];
		image_subset[1] = all_images[idx + 1];

		cout << "Orb: " << endl;
		Orb orb;
		orb.find_features(image_subset, idx);

		cout << "Brisk: " << endl;
		Brisk brisk;
		brisk.find_features(image_subset, idx);

		cout << "Akaze: " << endl;
		Akaze akaze;
		akaze.find_features(image_subset, idx);

		image_subset.empty();
	}

	cout << "MISSION ACCOMPLISHED." << endl;

	return 0;
}

