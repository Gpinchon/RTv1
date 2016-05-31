#include "../../adv_math.h"

double		vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		vec3_distance(t_vec3 v, t_vec3 v1)
{
	double a = v1.x - v.x;
	double b = v1.y - v.y;
	double c = v1.z - v.z;
	return (sqrt(a * a + b * b + c * c));
}

double		vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}