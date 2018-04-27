#include "stdafx.h"
#include "Brisk.h"


Brisk::Brisk() {
}


Brisk::~Brisk() {
}

void Brisk::find_features(vector<Mat> images, int idx) {

	image_params_.image_index = idx;

	num_images = static_cast<int> (images.size());
	image_features.resize(num_images);
	string features_out;

	for (int i = 0; i < num_images; i++) {

		features_out.clear();
		
		int thresh = 30;
		int octaves = 3;
		float patternScale = 1.0f;

		Ptr<BRISK> detector_desciptor;

		detector_desciptor = BRISK::create(thresh, octaves, patternScale);

		try {
			InputArray mask = noArray();
			detector_desciptor->detectAndCompute(images[i], mask, image_features[i].keypoints, image_features[i].descriptors);
		}
		catch (const std::exception& e) {
			cout << e.what() << endl;
		}

		cout << "Features in image: " << idx << ": " << image_features[i].keypoints.size() << endl;
		features_out += to_string(image_features[i].keypoints.size());
		CLOG(features_out, INFO, CSV_A);

		image_features[i].img_idx = i;
	}

	image_params_.image_features = image_features;
	image_params_.results_type = BRISK_R;
	image_params_.images = images;

	matcher(image_params_);
}
