#include "../../adv_math.h"

t_vec3	vec3_add(t_vec3 vector1, t_vec3 vector2)
{
	return ((t_vec3){
		vector1.x + vector2.x,
		vector1.y + vector2.y,
		vector1.z + vector2.z
	});
}

t_vec3	vec3_substract(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	});
}

t_vec3	vec3_multiply(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z
	});
}

t_vec3	vec3_cross(t_vec3 vector1, t_vec3 vector2)
{
	return ((t_vec3){
		vector1.y * vector2.z - vector1.z * vector2.y,
		vector1.z * vector2.x - vector1.x * vector2.z,
		vector1.x * vector2.y - vector1.y * vector2.x
	});
}

t_vec3	vec3_scale(t_vec3 v, t_vec3 v1)
{
	return ((t_vec3){
		v.x * v1.x,
		v.y * v1.y,
		v.z * v1.z
	});
}

t_vec3	vec3_divide(t_vec3 v, t_vec3 v1)
{
	return ((t_vec3){
		v.x / v1.x,
		v.y / v1.y,
		v.z / v1.z
	});
}

t_vec3	vec3_fscale(t_vec3 v, float d)
{
	return ((t_vec3){
		v.x * d,
		v.y * d,
		v.z * d
	});
}

t_vec3	vec3_fdivide(t_vec3 v, float d)
{
	return ((t_vec3){
		v.x / d,
		v.y / d,
		v.z / d
	});
}

t_vec3	vec3_abs(t_vec3 v)
{
	return ((t_vec3){
		fabs(v.x),
		fabs(v.y),
		fabs(v.z)
	});
}

t_vec3	vec3_negate(t_vec3 v)
{
	return ((t_vec3){
		-v.x,
		-v.y,
		-v.z
	});
}