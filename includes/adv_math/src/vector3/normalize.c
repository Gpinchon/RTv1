#include "../../adv_math.h"

t_vec3	vec3_normalize(t_vec3 v)
{
	double length;

	if ((length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z)))
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
	return (v);
}