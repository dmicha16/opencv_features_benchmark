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
	vector<Mat> all_images = orb_matcher.get_images();

	cout << all_images.size() << endl;
	vector<Mat> image_subset;

	int image_counter = all_images.size();
	WINPAUSE;

	for (size_t i = 0; i < all_images.size(); i++) {
		image_subset.push_back(all_images[i]);
		image_subset.push_back(all_images[i + 1]);

		cout << image_subset.size() << endl;
		WINPAUSE;

		orb_matcher.find_features(image_subset);
		orb_matcher.matcher(i);

		AkazeMatcher akaze_matcher;
		akaze_matcher.find_features(image_subset);
		akaze_matcher.matcher(i);

		BriskMatcher brisk_matcher;
		brisk_matcher.find_features(image_subset);
		brisk_matcher.matcher(i);

		if (image_counter == i) {
			break;
		}

		image_subset.clear();
	}
	return 0;
}

