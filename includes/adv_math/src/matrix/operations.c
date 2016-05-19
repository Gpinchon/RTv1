#include "../../adv_math.h"

t_vec3	m4_mult_vec3(t_mat4 m, t_vec3 v)
{
	return ((t_vec3){
		m.m[0] * v.x + (v.y * m.m[1] + (v.z * m.m[2] + m.m[3])),
		m.m[4] * v.x + (v.y * m.m[5] + (v.z * m.m[6] + m.m[7])),
		m.m[8] * v.x + (v.y * m.m[9] + (v.z * m.m[10] + m.m[11]))
	});
}
t_vec4	m4_mult_vec4(t_mat4 m, t_vec4 v)
{
	return ((t_vec4){
		m.m[0] * v.x + (v.y * m.m[1] + (v.z * m.m[2] + m.m[3] * v.w)),
		m.m[4] * v.x + (v.y * m.m[5] + (v.z * m.m[6] + m.m[7] * v.w)),
		m.m[8] * v.x + (v.y * m.m[9] + (v.z * m.m[10] + m.m[11] * v.w)),
		m.m[12] * v.x + (v.y * m.m[13] + (v.z * m.m[14] + m.m[15] * v.w))
	});
}