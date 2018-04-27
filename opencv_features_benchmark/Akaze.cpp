#include "stdafx.h"
#include "Akaze.h"


Akaze::Akaze() {
}


Akaze::~Akaze() {
}

void Akaze::find_features(vector<Mat> images, int idx) {

	image_params_.image_index = idx;

	num_images = static_cast<int> (images.size());
	image_features.resize(num_images);
	string features_out;

	for (int i = 0; i < num_images; i++) {

		features_out.clear();
		int descriptor_type = AKAZE::DESCRIPTOR_MLDB;
		int descriptor_size = 0;
		int descriptor_channels = 3;
		float threshold = 0.001f;
		int nOctaves = 4;
		int nOctaveLayers = 4;
		int diffusivity = KAZE::DIFF_PM_G2;

		Ptr<AKAZE> detector_desciptor;

		detector_desciptor = AKAZE::create(descriptor_type, descriptor_size, descriptor_channels,
			threshold, nOctaves, nOctaveLayers, diffusivity);

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
	image_params_.results_type = AKAZE_R;
	image_params_.images = images;

	matcher(image_params_);
}