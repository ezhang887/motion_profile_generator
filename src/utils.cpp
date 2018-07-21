#include <cmath>
#include <limits>

#include "../include/utils.h"

bool equals(double a, double b){
	const int ulp = 2;
	return std::abs(a-b) <= k_epsilon*std::abs(a+b)*ulp || std::abs(a-b) < std::numeric_limits<double>::min();
}
