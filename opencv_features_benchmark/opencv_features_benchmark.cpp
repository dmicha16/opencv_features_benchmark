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


int main()
{
	cv::ocl::setUseOpenCL(false);

	/******************************************* ORB *******************************************/

	OrbMatcher orb_matcher;
	vector<Mat> images = orb_matcher.get_images();
	orb_matcher.find_features(images);
	orb_matcher.matcher();

	/******************************************* AKAZE *******************************************/

	AkazeMatcher akaze_matcher;
	vector<Mat> images_1 = akaze_matcher.get_images();
	akaze_matcher.find_features(images_1);
	akaze_matcher.matcher();

	/******************************************* BRISK *******************************************/

	BriskMatcher brisk_matcher;
	vector<Mat> images_2 = brisk_matcher.get_images();
	brisk_matcher.find_features(images_2);
	brisk_matcher.matcher();

	return 0;
}

