#pragma once
#include "Benchmark.h"
class Brisk :
	public Benchmark {
public:
	Brisk();
	vector<ImageFeatures> get_brisk_image_features();
	void find_features(vector<Mat> images);
	~Brisk();

private:
	vector<ImageFeatures> image_features;
	int num_images;
};
