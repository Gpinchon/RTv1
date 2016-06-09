#include "../../adv_math.h"

enum e_bool	float_equal(float a, float b)
{
	return (a - b <= FLOAT_ZERO) || (b - a <= FLOAT_ZERO);
}