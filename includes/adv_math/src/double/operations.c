#include "../../adv_math.h"

enum e_bool	double_equal(double a, double b)
{
	return (a - b <= DOUBLE_ZERO) || (b - a <= DOUBLE_ZERO);
}