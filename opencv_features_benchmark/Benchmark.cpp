#include "stdafx.h"
#include "Benchmark.h"


Benchmark::Benchmark() {

}

Benchmark::~Benchmark() {
}

void Benchmark::draw_keypoints(vector<Mat> images, vector<ImageFeatures> image_features, vector<MatchesInfo> pairwise_matches) {
	
}

void Benchmark::draw_my_matches(ImageParams image_params) {

	string output_location = construct_file_name(image_params.matcher_type, image_params.results_type, image_params.image_index);
	int image_idx = image_params.image_index;
	cout << "image_params.images.size(): " << image_params.images.size() << endl;
	vector<Mat> images = image_params.images;

	vector<DMatch> matches = image_params.pairwise_matches[1].matches;
	vector<char> mask(matches.size(), 1);
	Mat output_img;

	try {
		drawMatches(images[0], image_params.image_features[0].keypoints,
			images[1], image_params.image_features[1].keypoints, matches, output_img, Scalar::all(-1),
			Scalar::all(-1), mask, DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}

	Mat outImg;
	resize(output_img, outImg, cv::Size(), 1, 1);
	//imshow("Matching", outImg);
	imwrite(output_location, outImg);
	printf("Image result written.\n");
}

string Benchmark::construct_file_name(string matcher_type, ResultsType results_type, int image_index) {

	string output_location = "../opencv_features_benchmark/Images";
	/*string c;
	int r1, r2, r3;
	srand(time(NULL));

	for (int i = 0; i < 3; i++){
		r1 = rand() % 26;
		r2 = rand() % 26;
		r3 = rand() % 26;
		c = 'a' + r1;
		c += 'a' + r2;
		c += 'a' + r3;
	}*/

	switch (results_type) {
	case ORB_R:
		output_location += "/ORB/" + matcher_type + "_" + to_string(image_index) + "-" + to_string(image_index + 1) + ".jpg";
		break;
	case BRISK_R:
		output_location += "/BRISK/" + matcher_type + "_" + to_string(image_index) + "-" + to_string(image_index + 1) + ".jpg";
		break;
	case AKAZE_R:
		output_location += "/AKAZE/" + matcher_type + "_" + to_string(image_index) + "-" + to_string(image_index + 1) + ".jpg";
		break;
	}
	return output_location;
}

void Benchmark::matcher(ImageParams image_params) {

	vector<ImageFeatures> image_features = image_params.image_features;

	float match_conf = 0.3f;
	bool try_cuda = false;
	int range_width = -1;

	vector<MatchesInfo> pairwise_matches;
	Ptr<FeaturesMatcher> current_matcher;
	string matcher_type;

	for (size_t i = 1; i < 4; i++) {

		switch (i) {
		case 1:
			current_matcher = makePtr<BestOf2NearestMatcher>(false, try_cuda, match_conf);
			matcher_type = "BestOf2NearestMatcher";
			image_params.matcher_type = matcher_type;
			printf("BestOf2NearestMatcher\n");
			break;
		case 2:
			current_matcher = makePtr<BestOf2NearestRangeMatcher>(false, try_cuda, match_conf);
			matcher_type = "BestOf2NearestRangeMatcher";
			image_params.matcher_type = matcher_type;
			printf("BestOf2NearestRangeMatcher\n");
			break;
		case 3:
			current_matcher = makePtr<AffineBestOf2NearestMatcher>(false, try_cuda, match_conf);
			matcher_type = "AffineBestOf2NearestMatcher";
			image_params.matcher_type = matcher_type;
			printf("AffineBestOf2NearestMatcher\n");
			break;
		}

		try {
			(*current_matcher)(image_features, pairwise_matches);
		}
		catch (const std::exception& e) {
			cout << e.what() << endl;
		}

		image_params.pairwise_matches = pairwise_matches;

		draw_my_matches(image_params);
		pairwise_matches.clear();
	}
}
