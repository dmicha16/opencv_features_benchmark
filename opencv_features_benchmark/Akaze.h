#pragma once
#include "Benchmark.h"
class Akaze :
	public Benchmark {
public:
	Akaze();
	~Akaze();
	void find_features(vector<Mat> images, int idx);
private:
	vector<ImageFeatures> image_features;
	ImageParams image_params_;
	int num_images;
};

