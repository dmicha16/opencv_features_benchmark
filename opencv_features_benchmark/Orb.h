#pragma once
#include "Benchmark.h"
class Orb :
	public Benchmark {
public:
	Orb();
	vector<ImageFeatures> get_orb_image_features();
	void find_features(vector<Mat> images);
	~Orb();

private:
	vector<ImageFeatures> image_features;
	int num_images;
};

