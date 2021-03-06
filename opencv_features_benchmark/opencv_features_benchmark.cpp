// opencv_features_benchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Benchmark.h"
#include "Orb.h"
#include "Akaze.h"
#include "Brisk.h"
#include "ImageHandler.h"
#include "RoiCalculator.h"

int main() {

	INIT_CLOGGING;
	CLOGGING_TIMER;
	ADD_FILE("clogging.csv");
	cv::ocl::setUseOpenCL(false);

	String path = "../opencv_features_benchmark/Images/";
	ImageHandler image_handler(path);
	vector<Mat> all_images = image_handler.get_images();
	vector<String> image_names = image_handler.get_short_names();

	RoiCalculator roi_calculator;
	roi_calculator.set_images(all_images);
	roi_calculator.calculate_roi(6);
	WINPAUSE;

	cout << all_images.size() << endl;
	vector<Mat> image_subset(2);
	string iteriation;
	string current_images;

	CLOG_T("Global timer", START);
	string timer;

	for (int idx = 0; idx < all_images.size(); idx++) {

		if ((idx + 1) == all_images.size()) {
			break;
		}

		iteriation = "ITERIATION: " + to_string(idx) + "-" + to_string(idx + 1);
		current_images = "CURRENT IMAGES: " + image_names[idx] + "-" + image_names[idx + 1];
		CLOG(iteriation, NOTICE, CSV);
		CLOG(current_images, NOTICE, CSV);
		cout << iteriation << endl;;

		image_subset[0] = all_images[idx];
		image_subset[1] = all_images[idx + 1];
		cout << image_subset[0].size << endl;	

		cout << "Orb: " << endl;
		Orb orb;
		timer = "ORB w/ images: " + image_names[idx] + "-" + image_names[idx + 1];
		CLOG_T(timer, START);
		CLOG("Currently working ORB: ", INFO, CSV);
		orb.find_features(image_subset, idx);
		CLOG_T(timer, END);
		timer = "";

		cout << "Brisk: " << endl;
		Brisk brisk;
		timer = "BRISK w/ images: " + image_names[idx] + "-" + image_names[idx + 1];
		CLOG_T(timer, START);
		CLOG("Currently working BRISK: ", INFO, CSV);
		brisk.find_features(image_subset, idx);
		CLOG_T(timer, END);
		timer = "";

		cout << "Akaze: " << endl;
		Akaze akaze;
		timer = "AKAZE w/ images: " + image_names[idx] + "-" + image_names[idx + 1];
		CLOG_T(timer, START);
		CLOG("Currently working AKAZE: ", INFO, CSV);
		akaze.find_features(image_subset, idx);
		CLOG_T(timer, END);
		timer = "";

		image_subset.empty();
		iteriation = "";
		timer = "";
	}

	CLOG_T("Global timer", END);
	CLOG("MISSION ACCOMPLISHED.", INFO, CSV);
	cout << "MISSION ACCOMPLISHED." << endl;
	WINPAUSE;

	return 0;
}

