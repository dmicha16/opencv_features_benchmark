#pragma once
#include "Orb.h"

class OrbMatcher :
	public Orb {
public:
	OrbMatcher();
	~OrbMatcher();
	void matcher(int image_index);
private:
};

