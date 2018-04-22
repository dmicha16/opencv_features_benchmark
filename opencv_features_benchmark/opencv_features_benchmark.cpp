// opencv_features_benchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Benchmark.h"
#include "Orb.h"
#include "Akaze.h"
#include "Brisk.h"
#include "OrbMatcher.h"
#include "AkazeMatcher.h"
#include "BriskMatcher.h"
#include "ImageHandler.h"


int main()
{
	cv::ocl::setUseOpenCL(false);

	/******************************************* ORB *******************************************/

	String path = "../opencv_features_benchmark/Images/";

	ImageHandler image_handler(path);
	vector<Mat> all_images = image_handler.get_images();

	Orb orb;
	orb.find_features(all_images);

	Brisk brisk;
	brisk.find_features(all_images);

	Akaze akaze;
	akaze.find_features(all_images);

	WINPAUSE;
	/*cout << all_images.size() << endl;
	vector<Mat> image_subset(2);

	int image_counter = all_images.size();
	WINPAUSE;

	for (size_t i = 0; i < all_images.size(); i++) {

		image_subset.clear();
	}*/
	return 0;
}

