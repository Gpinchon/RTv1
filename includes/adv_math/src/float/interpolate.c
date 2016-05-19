#include "../../adv_math.h"

float	float_lerp(float start, float end, float percent)
{
	percent = (percent > 1.f) ? 1.f : percent;
	percent = (percent < 0.f) ? 0.f : percent;
	return (start * (1 - percent) + end * percent);
}

float	float_qlerp(float start, float end, float amount)
{
	amount = (amount > 1.f) ? 1.f : amount;
	amount = (amount < 0.f) ? 0.f : amount;
	amount = pow(amount, 2) * (3.f - (2.f * amount));
	return (((end - start) * amount) + start);
}

float	float_step(float a, float x)
{
	return (x >= a);
}
