#include "stdafx.h"
#include "Matcher.h"


Matcher::Matcher(ToMatch features_type) {

	vector<Mat> images = Benchmark::get_images();
	Orb::find_features(images);
	matcher_bestof2_nearest_(features_type);
}


Matcher::~Matcher() {
}

void Matcher::matcher_bestof2_nearest_(ToMatch features_type) {

	float match_conf = 0.3f;
	bool try_cuda = false;
	int range_width = -1;

	vector<ImageFeatures> image_features;
	vector<MatchesInfo> pairwise_matches;

	switch (features_type) {
	case ToMatch::AKAZETYPE:
		//image_features = get_image_features();
	case ToMatch::ORBTYPE:
		image_features = Orb::get_orb_image_features();
	case ToMatch::BRISKTYPE:
		//image_features = get_image_features();
	default:
		break;
	}

	Ptr<FeaturesMatcher> current_matcher = makePtr<BestOf2NearestMatcher>(false, try_cuda, match_conf);

	try {
		(*current_matcher)(image_features, pairwise_matches);
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}

	Benchmark::draw_my_matches(image_features, pairwise_matches);
}
