// opencv_features_benchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Benchmark.h"
#include "Orb.h"
#include "Akaze.h"
#include "Brisk.h"
#include "OrbMatcher.h"


int main()
{
	cv::ocl::setUseOpenCL(false);
	OrbMatcher orb_matcher;
	vector<Mat> images = orb_matcher.get_images();
	orb_matcher.find_features(images);
	orb_matcher.matcher_bestof2_nearest_();

	return 0;
}

