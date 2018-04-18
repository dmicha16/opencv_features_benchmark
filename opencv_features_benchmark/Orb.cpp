#include "stdafx.h"
#include "Orb.h"

Orb::Orb() {
}

Orb::~Orb() {
}

vector<ImageFeatures> Orb::get_orb_image_features() {
	return image_features;
}

void Orb::find_features(vector<Mat> images) {

	num_images = static_cast<int> (images.size());
	image_features.resize(num_images);
	string features_out = "Features in image #";

	for (int i = 0; i < num_images; i++) {		
		float scaleFactor = 1.2f;
		int nlevels = 8;
		int edgeThreshold = 31;
		int firstLevel = 0;
		int WTA_K = 2;
		int scoreType = ORB::HARRIS_SCORE;
		int patchSize = 31;
		int fastThreshold = 20;

		Ptr<ORB> detector_desciptor;

		detector_desciptor = ORB::create(1500, scaleFactor, nlevels, edgeThreshold,
			firstLevel, WTA_K, scoreType, patchSize, fastThreshold);

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
