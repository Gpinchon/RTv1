#include "../../adv_math.h"

float		vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float		vec3_distance(t_vec3 v, t_vec3 v1)
{
	float a = v1.x - v.x;
	float b = v1.y - v.y;
	float c = v1.z - v.z;
	return (sqrt(a * a + b * b + c * c));
}

float		vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}