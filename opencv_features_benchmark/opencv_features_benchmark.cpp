// opencv_features_benchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Benchmark.h"
#include "Orb.h"
#include "Akaze.h"
#include "Brisk.h"
#include "Matcher.h"


int main()
{
	cv::ocl::setUseOpenCL(false);
	Matcher matcher(ToMatch::ORBTYPE);
	return 0;
}

