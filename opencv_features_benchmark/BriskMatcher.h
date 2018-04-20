#pragma once
#include "Brisk.h"
class BriskMatcher :
	public Brisk {
public:
	BriskMatcher();
	~BriskMatcher();
	void matcher(int image_index);
};

