#include "../../adv_math.h"

enum e_bool	float_equal(float a, float b)
{
	return (fabs(a - b) <= FLOAT_ZERO);
}