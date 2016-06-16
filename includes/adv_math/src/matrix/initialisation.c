#include "../../adv_math.h"

t_mat4	m4_identity(void)
{
	return ((t_mat4){ .m = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	}});
}

t_mat4	m4_zero(void)
{
	return ((t_mat4){ .m = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	}});
}

t_mat3	m3_identity(void)
{
	return ((t_mat3){ .m = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
	}});
}

t_mat3	m3_zero(void)
{
	return ((t_mat3){ .m = {
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
	}});
}