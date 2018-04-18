#include "stdafx.h"
#include "Brisk.h"


Brisk::Brisk() {
}


Brisk::~Brisk() {
}

vector<ImageFeatures> Brisk::get_brisk_image_features() {
	return image_features;
}

void Brisk::find_features(vector<Mat> images) {

	num_images = static_cast<int> (images.size());
	image_features.resize(num_images);
	string features_out = "Features in image #";

	for (int i = 0; i < num_images; i++) {
		
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

		cout << "Features in image #" << image_features[i].keypoints.size() << endl;

		image_features[i].img_idx = i;
	}
}
