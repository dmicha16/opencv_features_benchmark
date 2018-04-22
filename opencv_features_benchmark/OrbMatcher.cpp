#include "stdafx.h"
#include "OrbMatcher.h"


OrbMatcher::OrbMatcher() {
}

OrbMatcher::~OrbMatcher() {
}

void OrbMatcher::matcher(int image_index) {

	float match_conf = 0.3f;
	bool try_cuda = false;
	int range_width = -1;

	vector<ImageFeatures> image_features = get_orb_image_features();
	vector<MatchesInfo> pairwise_matches;
	Ptr<FeaturesMatcher> current_matcher;
	string matcher_type;

	for (size_t i = 1; i < 4; i++) {

		switch (i) {
		case 1:
			current_matcher = makePtr<BestOf2NearestMatcher>(false, try_cuda, match_conf);
			matcher_type = "BestOf2NearestMatcher";
			printf("BestOf2NearestMatcher\n");
			break;
		case 2:
			current_matcher = makePtr<BestOf2NearestRangeMatcher>(false, try_cuda, match_conf);
			matcher_type = "BestOf2NearestRangeMatcher";
			printf("BestOf2NearestRangeMatcher\n");
			break;
		case 3:
			current_matcher = makePtr<AffineBestOf2NearestMatcher>(false, try_cuda, match_conf);
			matcher_type = "AffineBestOf2NearestMatcher";
			printf("AffineBestOf2NearestMatcher\n");
			break;
		}

		try {
			(*current_matcher)(image_features, pairwise_matches);
		}
		catch (const std::exception& e) {
			cout << e.what() << endl;
		}

		//draw_my_matches(image_features, pairwise_matches, matcher_type, ORB_R, image_index);
		pairwise_matches.clear();
	}
}
