#pragma once
#include "Akaze.h"
#include "Orb.h"
#include "Brisk.h"

class OrbMatcher :
	public Orb {
public:
	OrbMatcher();
	~OrbMatcher();
	void matcher_bestof2_nearest_();
private:
	
	void matcher_bestof2nearest_range_(ToMatch features_type);
	void matcher_affinebestof2_nearest_(ToMatch features_type);
};

