#include "stdafx.h"
#include "Benchmark.h"

struct SortOperator {
	bool operator() (int i, int j) {
		return (i < j);
	}
} sort_operator_;

Benchmark::Benchmark() {
	ADD_FILE("clogging.csv");
}

Benchmark::~Benchmark() {
}
void Benchmark::draw_keypoints(vector<Mat> images, vector<ImageFeatures> image_features, vector<MatchesInfo> pairwise_matches) {
	
}

void Benchmark::draw_matches_(const ImageParams image_params) {

	string output_location = construct_file_name_(image_params.matcher_type, image_params.results_type, image_params.image_index);
	size_t image_idx = image_params.image_index;
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

	Mat resized_image;
	resize(output_img, resized_image, cv::Size(), 1, 1);

	if (imwrite(output_location, resized_image)) {
		//printf("Image result written.\n");
		//CLOG("Image result successfully written.", INFO);
	}		
	else {
		//printf("Image failed to write.\n");
		CLOG("Image failed to write.", ERR, CSV);
	}
		
}

string Benchmark::construct_file_name_(string matcher_type, ResultsType results_type, int image_index) {

	string output_location = "../opencv_features_benchmark/Images";

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

void Benchmark::threshold_calculator_(const ImageParams image_params) {

	vector<DMatch> matches = image_params.pairwise_matches[1].matches;
	vector<float> distances;
	vector<float> thresholds;

	for (size_t i = 0; i < matches.size(); i++) {
		distances.push_back(matches[i].distance);
	}

	std::sort (distances.begin(), distances.end(), sort_operator_);
	for (float i = 0.1; i < 0.5; i+=0.1) {
		thresholds.push_back(distances.size() * i);
	}

	float avarage = 0;
	for (size_t i = 0; i < distances.size(); i++) {
		avarage += distances[i];
	}
	avarage = avarage / distances.size();
	string av = to_string(avarage);

	CLOG(av, INFO, CSV_A);
}

void Benchmark::matcher(ImageParams image_params) {

	vector<ImageFeatures> image_features = image_params.image_features;

	float match_conf = 0.3f;
	bool try_cuda = false;
	int range_width = -1;

	vector<MatchesInfo> pairwise_matches;
	Ptr<FeaturesMatcher> current_matcher;
	string matcher_type;
	string number_of_matches;
	string number_of_matches_clog;

	for (size_t i = 1; i < 4; i++) {

		switch (i) {
		case 1:
			current_matcher = makePtr<BestOf2NearestMatcher>(false, try_cuda, match_conf);
			matcher_type = "DEFAULT";
			image_params.matcher_type = matcher_type;
			CLOG(matcher_type, INFO, CSV);
			printf("DEFAULT.\n");
			break;
		case 2:
			current_matcher = makePtr<BestOf2NearestRangeMatcher>(false, try_cuda, match_conf);
			matcher_type = "RANGE";
			image_params.matcher_type = matcher_type;
			CLOG(matcher_type, INFO, CSV);
			printf("RANGE.\n");
			break;
		case 3:
			current_matcher = makePtr<AffineBestOf2NearestMatcher>(false, try_cuda, match_conf);
			matcher_type = "AFFINE";
			image_params.matcher_type = matcher_type;
			CLOG(matcher_type, INFO, CSV);
			printf("AFFINE.\n");
			break;
		}

		try {
			(*current_matcher)(image_features, pairwise_matches);
		}
		catch (const std::exception& e) {
			cout << e.what() << endl;
		}

		number_of_matches = "Total number of matches:, " + to_string(pairwise_matches[1].matches.size());
		number_of_matches_clog = to_string(pairwise_matches[1].matches.size());
		CLOG(" ", INFO, CSV_A);
		CLOG(" ", INFO, CSV_A);
		CLOG(number_of_matches_clog, INFO, CSV_A);

		image_params.pairwise_matches = pairwise_matches;

		threshold_calculator_(image_params);
		draw_matches_(image_params);
		pairwise_matches.clear();
		number_of_matches = "";
	}
}
