#pragma once
#include "Benchmark.h"
class Brisk :
	public Benchmark {
public:
	Brisk();
	void find_features(vector<Mat> images, int idx);
	~Brisk();

private:
	vector<ImageFeatures> image_features;
	ImageParams image_params_;
	int num_images;
};

