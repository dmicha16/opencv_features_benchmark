#include "stdafx.h"
#include "ImageHandler.h"


ImageHandler::ImageHandler(string path) {
	read_images_(path);
}

ImageHandler::~ImageHandler() {
}

vector<Mat> ImageHandler::get_images() {
	return images_;
}

vector<String> ImageHandler::get_image_names() {
	return img_names_;
}

vector<String> ImageHandler::get_short_names() {
	return short_img_names_;
}

void ImageHandler::read_images_(string path) {
	vector<String> photos;

	/*for (auto & file : experimental::filesystem::directory_iterator(path))
	cout << file << endl;*/

	glob(path, photos, false);

	cout << "Images read: " << photos.size() << endl;
	WINPAUSE;
	for (int i = 0; i < photos.size(); i++) {
		img_names_.push_back(photos[i]);
	}

	num_images_ = static_cast <int> (img_names_.size());
	vector<Size> full_img_sizes(num_images_);
	shorten_image_names_(img_names_);

	images_.resize(num_images_);
	images_ = upload_images_(images_, full_img_sizes);
}

vector<Mat> ImageHandler::upload_images_(vector<Mat> images, vector<Size> full_img_sizes) {

	Mat full_img, img;

	double work_megapix = 0.6;
	double seam_megapix = 0.1;
	double work_scale = 1, seam_scale = 1, compose_scale = 1, seam_work_aspect = 1;
	bool is_work_scale_set = false, is_seam_scale_set = false, is_compose_scale_set = false;

	for (int i = 0; i < num_images_; ++i) {
		full_img = imread(img_names_[i]);
		full_img_sizes[i] = full_img.size();

		if (work_megapix < 0) {
			img = full_img;
			work_scale = 1;
			is_work_scale_set = true;
		}
		else {
			if (!is_work_scale_set) {
				work_scale = min(1.0, sqrt(work_megapix * 1e6 / full_img.size().area()));
				is_work_scale_set = true;
			}
			resize(full_img, img, Size(), work_scale, work_scale, INTER_LINEAR_EXACT);
		}
		if (!is_seam_scale_set) {
			seam_scale = min(1.0, sqrt(seam_megapix * 1e6 / full_img.size().area()));
			seam_work_aspect = seam_scale / work_scale;
			is_seam_scale_set = true;
		}
		images[i] = img.clone();
	}
	full_img.release();
	img.release();
	return images;
}

void ImageHandler::shorten_image_names_(vector<String> img_names) {

	string img_name;
	string temp;
	for (size_t i = 0; i < img_names.size(); i++) {
		temp.assign(img_names[i]);
		for (size_t j = 0; j < temp.size(); j++) {
			if (temp.at(j) == '\\') {
				for (size_t k = (j + 1); k < temp.size(); k++) {
					img_name += temp.at(k);
				}
				break;
			}
		}
		short_img_names_.push_back(img_name);
		img_name.clear();
		temp.clear();
	}
}
