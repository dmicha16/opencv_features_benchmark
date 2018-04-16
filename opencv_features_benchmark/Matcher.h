#pragma once
#include "Akaze.h"
#include "Orb.h"
#include "Brisk.h"

class Matcher :
	public Akaze, public Orb, public Brisk {
public:
	Matcher(ToMatch features_type);
	~Matcher();
private:
	void matcher_bestof2_nearest_(ToMatch features_type);
	void matcher_bestof2nearest_range_(ToMatch features_type);
	void matcher_affinebestof2_nearest_(ToMatch features_type);
};

