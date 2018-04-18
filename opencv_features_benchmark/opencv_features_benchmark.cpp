// opencv_features_benchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Benchmark.h"
#include "Orb.h"
#include "Akaze.h"
#include "Brisk.h"
#include "OrbMatcher.h"
#include "AkazeMatcher.h"


int main()
{
	cv::ocl::setUseOpenCL(false);

	/******************************************* ORB *******************************************/

	OrbMatcher orb_matcher;
	vector<Mat> images = orb_matcher.get_images();
	orb_matcher.find_features(images);
	orb_matcher.matcher();
	//orb_matcher.~OrbMatcher;

	/******************************************* BRISK *******************************************/

	AkazeMatcher akaze_matcher;
	vector<Mat> images_1 = akaze_matcher.get_images();
	akaze_matcher.find_features(images_1);
	akaze_matcher.matcher();
	//akaze_matcher.~AkazeMatcher;

	return 0;
}

