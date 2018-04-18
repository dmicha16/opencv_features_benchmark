#pragma once
#include "Akaze.h"
class AkazeMatcher :
	public Akaze {
public:
	AkazeMatcher();
	~AkazeMatcher();
	void matcher();
};

