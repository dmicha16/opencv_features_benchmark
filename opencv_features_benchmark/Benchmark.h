#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <filesystem>

#include "opencv2/opencv_modules.hpp"
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching/detail/autocalib.hpp"
#include "opencv2/stitching/detail/blenders.hpp"
#include "opencv2/stitching/detail/timelapsers.hpp"
#include "opencv2/stitching/detail/camera.hpp"
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/motion_estimators.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include "opencv2/stitching/warpers.hpp"
#include "opencv2/core/ocl.hpp"

#pragma region namespaces
using namespace std;
using namespace cv;
using namespace cv::detail;
#pragma endregion

#ifdef _WIN32
#define WINPAUSE system("pause")
#endif

enum ToMatch { AKAZETYPE = 1, ORBTYPE = 2, BRISKTYPE = 3 };

class Benchmark {
public:
	Benchmark();
	~Benchmark();
	vector<Mat> get_images();
	void draw_keypoints(vector<Mat> images, vector<ImageFeatures> image_features, vector<MatchesInfo> pairwise_matches);
	void draw_my_matches(vector<ImageFeatures> image_features, vector<MatchesInfo> pairwise_matches);

private:
	int num_images;
	vector<String> img_names;
	vector<Mat> images;
	void read_images_(string path);
	void upload_images_(vector<Mat> images, vector<Size> full_img_sizes);
};

