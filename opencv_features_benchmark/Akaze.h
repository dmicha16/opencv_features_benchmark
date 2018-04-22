#pragma once
#include "Benchmark.h"
class Akaze :
	public Benchmark {
public:
	Akaze();
	~Akaze();
	void find_features(vector<Mat> images);
	vector<ImageFeatures> get_akaze_image_features();
private:
	vector<ImageFeatures> image_features;
	ImageParams image_params_;
	int num_images;
};

