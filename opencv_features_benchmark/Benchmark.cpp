#include "stdafx.h"
#include "Benchmark.h"


Benchmark::Benchmark() {
	String path = "../opencv_features_benchmark/Images/";
	read_images_(path);
}

Benchmark::~Benchmark() {
}

vector<Mat> Benchmark::get_images() {
	vector<Mat> return_images = images;
	WINPAUSE;
	return return_images;
}

void Benchmark::draw_keypoints(vector<Mat> images, vector<ImageFeatures> image_features, vector<MatchesInfo> pairwise_matches) {
	
}

void Benchmark::draw_my_matches(vector<ImageFeatures> image_features, vector<MatchesInfo> pairwise_matches) {

	String output_location = "../opencv_features_benchmarke/Images/test_1.jpg";
	vector<Mat> images = get_images();
	vector<DMatch> matches = pairwise_matches[1].matches;
	vector<char> mask(matches.size(), 1);
	Mat output_img;

	try {
		drawMatches(images[0], image_features[0].keypoints, images[1], image_features[0].keypoints, matches, output_img, Scalar::all(-1),
			Scalar::all(-1), mask, DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}

	Mat outImg;
	resize(output_img, outImg, cv::Size(), 1, 1);
	imshow("Matching", outImg);
	waitKey(0);

	imwrite(output_location, outImg);
}

void Benchmark::read_images_(string path) {

	vector<String> photos;

	for (auto & file : experimental::filesystem::directory_iterator(path))
		cout << file << endl;

	glob(path, photos, false);

	cout << "Images read: " << photos.size() << endl;
	for (int i = 0; i < photos.size(); i++) {
		img_names.push_back(photos[i]);
	}

	num_images = static_cast <int> (img_names.size());
	vector<Size> full_img_sizes(num_images);

	images.resize(num_images);
	Benchmark::upload_images_(images, full_img_sizes);
}

void Benchmark::upload_images_(vector<Mat> images, vector<Size> full_img_sizes) {

	Mat full_img, img;
	double work_megapix = 0.6;
	double seam_megapix = 0.1;
	double work_scale = 1, seam_scale = 1, compose_scale = 1, seam_work_aspect = 1;
	bool is_work_scale_set = false, is_seam_scale_set = false, is_compose_scale_set = false;

	for (int i = 0; i < num_images; ++i) {
		full_img = imread(img_names[i]);
		full_img_sizes[i] = full_img.size();

		if (work_megapix < 0) {
			img = full_img;
			work_scale = 1;
			is_work_scale_set = true;
		}
		else {
			if (!is_work_scale_set) {
				work_scale = min(1.0, sqrt(work_megapix * 1e6 / full_img.size().area()));
				is_work_scale_set = true;
			}
			resize(full_img, img, Size(), work_scale, work_scale, INTER_LINEAR_EXACT);
		}
		if (!is_seam_scale_set) {
			seam_scale = min(1.0, sqrt(seam_megapix * 1e6 / full_img.size().area()));
			seam_work_aspect = seam_scale / work_scale;
			is_seam_scale_set = true;
		}
		images[i] = img.clone();
	}
	full_img.release();
	img.release();
}
