#include "../../adv_math.h"

t_vec3	m3_mult_vec3(t_mat3 m, t_vec3 v)
{
	return ((t_vec3){
		v.x * m.m[0] + v.y * m.m[3] + v.z * m.m[6],
    	v.x * m.m[1] + v.y * m.m[4] + v.z * m.m[7],
    	v.x * m.m[2] + v.y * m.m[5] + v.z * m.m[8]
	});
}