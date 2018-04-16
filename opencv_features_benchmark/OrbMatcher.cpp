#include "stdafx.h"
#include "OrbMatcher.h"


OrbMatcher::OrbMatcher() {
}


OrbMatcher::~OrbMatcher() {
}

void OrbMatcher::matcher_bestof2_nearest_() {

	float match_conf = 0.3f;
	bool try_cuda = false;
	int range_width = -1;

	vector<ImageFeatures> image_features = get_orb_image_features();
	vector<MatchesInfo> pairwise_matches;

	Ptr<FeaturesMatcher> current_matcher = makePtr<BestOf2NearestMatcher>(false, try_cuda, match_conf);

	try {
		(*current_matcher)(image_features, pairwise_matches);
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}

	draw_my_matches(image_features, pairwise_matches);
}
