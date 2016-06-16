#include "../../adv_math.h"

t_vec3	m4_mult_vec3(t_mat4 m, t_vec3 v)
{
	return ((t_vec3){
		v.x * m.m[0] + v.y * m.m[4] + v.z * m.m[8] + m.m[12],
		v.x * m.m[1] + v.y * m.m[5] + v.z * m.m[9] + m.m[13],
		v.x * m.m[2] + v.y * m.m[6] + v.z * m.m[10] + m.m[14]
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

static void	m4_inverse1(t_mat4 *t, const t_mat4 i)
{
	t->m[0] = i.m[5]  * i.m[10] * i.m[15] - i.m[5]  * i.m[11] * i.m[14] -
		i.m[9]  * i.m[6]  * i.m[15] + i.m[9]  * i.m[7]  * i.m[14] +
		i.m[13] * i.m[6]  * i.m[11] - i.m[13] * i.m[7]  * i.m[10];
	t->m[4] = -i.m[4]  * i.m[10] * i.m[15] + i.m[4]  * i.m[11] * i.m[14] +
		i.m[8]  * i.m[6]  * i.m[15] - i.m[8]  * i.m[7]  * i.m[14] -
		i.m[12] * i.m[6]  * i.m[11] + i.m[12] * i.m[7]  * i.m[10];
	t->m[8] = i.m[4]  * i.m[9] * i.m[15] - i.m[4]  * i.m[11] * i.m[13] -
		i.m[8]  * i.m[5] * i.m[15] + i.m[8]  * i.m[7] * i.m[13] +
		i.m[12] * i.m[5] * i.m[11] - i.m[12] * i.m[7] * i.m[9];
	t->m[12] = -i.m[4]  * i.m[9] * i.m[14] + i.m[4]  * i.m[10] * i.m[13] +
		i.m[8]  * i.m[5] * i.m[14] - i.m[8]  * i.m[6] * i.m[13] -
		i.m[12] * i.m[5] * i.m[10] + i.m[12] * i.m[6] * i.m[9];
	t->m[1] = -i.m[1]  * i.m[10] * i.m[15] + i.m[1]  * i.m[11] * i.m[14] +
		i.m[9]  * i.m[2] * i.m[15] - i.m[9]  * i.m[3] * i.m[14] -
		i.m[13] * i.m[2] * i.m[11] + i.m[13] * i.m[3] * i.m[10];
	t->m[5] = i.m[0]  * i.m[10] * i.m[15] - i.m[0]  * i.m[11] * i.m[14] -
		i.m[8]  * i.m[2] * i.m[15] + i.m[8]  * i.m[3] * i.m[14] +
		i.m[12] * i.m[2] * i.m[11] - i.m[12] * i.m[3] * i.m[10];
	t->m[9] = -i.m[0]  * i.m[9] * i.m[15] + i.m[0]  * i.m[11] * i.m[13] +
		i.m[8]  * i.m[1] * i.m[15] - i.m[8]  * i.m[3] * i.m[13] -
		i.m[12] * i.m[1] * i.m[11] + i.m[12] * i.m[3] * i.m[9];
	t->m[13] = i.m[0]  * i.m[9] * i.m[14] - i.m[0]  * i.m[10] * i.m[13] -
		i.m[8]  * i.m[1] * i.m[14] + i.m[8]  * i.m[2] * i.m[13] +
		i.m[12] * i.m[1] * i.m[10] - i.m[12] * i.m[2] * i.m[9];
}

static void	m4_inverse2(t_mat4 *t, const t_mat4 i)
{
	t->m[2] = i.m[1]  * i.m[6] * i.m[15] - i.m[1]  * i.m[7] * i.m[14] -
		i.m[5]  * i.m[2] * i.m[15] + i.m[5]  * i.m[3] * i.m[14] +
		i.m[13] * i.m[2] * i.m[7] - i.m[13] * i.m[3] * i.m[6];
	t->m[6] = -i.m[0]  * i.m[6] * i.m[15] + i.m[0]  * i.m[7] * i.m[14] +
		i.m[4]  * i.m[2] * i.m[15] - i.m[4]  * i.m[3] * i.m[14] -
		i.m[12] * i.m[2] * i.m[7] + i.m[12] * i.m[3] * i.m[6];
	t->m[10] = i.m[0]  * i.m[5] * i.m[15] - i.m[0]  * i.m[7] * i.m[13] -
		i.m[4]  * i.m[1] * i.m[15] + i.m[4]  * i.m[3] * i.m[13] +
		i.m[12] * i.m[1] * i.m[7] - i.m[12] * i.m[3] * i.m[5];
	t->m[14] = -i.m[0]  * i.m[5] * i.m[14] + i.m[0]  * i.m[6] * i.m[13] +
		i.m[4]  * i.m[1] * i.m[14] - i.m[4]  * i.m[2] * i.m[13] -
		i.m[12] * i.m[1] * i.m[6] + i.m[12] * i.m[2] * i.m[5];
	t->m[3] = -i.m[1] * i.m[6] * i.m[11] + i.m[1] * i.m[7] * i.m[10] +
		i.m[5] * i.m[2] * i.m[11] - i.m[5] * i.m[3] * i.m[10] -
		i.m[9] * i.m[2] * i.m[7] + i.m[9] * i.m[3] * i.m[6];
	t->m[7] = i.m[0] * i.m[6] * i.m[11] - i.m[0] * i.m[7] * i.m[10] -
		i.m[4] * i.m[2] * i.m[11] + i.m[4] * i.m[3] * i.m[10] +
		i.m[8] * i.m[2] * i.m[7] - i.m[8] * i.m[3] * i.m[6];
	t->m[11] = -i.m[0] * i.m[5] * i.m[11] + i.m[0] * i.m[7] * i.m[9] +
		i.m[4] * i.m[1] * i.m[11] - i.m[4] * i.m[3] * i.m[9] -
		i.m[8] * i.m[1] * i.m[7] + i.m[8] * i.m[3] * i.m[5];
	t->m[15] = i.m[0] * i.m[5] * i.m[10] - i.m[0] * i.m[6] * i.m[9] -
		i.m[4] * i.m[1] * i.m[10] + i.m[4] * i.m[2] * i.m[9] +
		i.m[8] * i.m[1] * i.m[6] - i.m[8] * i.m[2] * i.m[5];
}

t_mat4	m4_invert(const t_mat4 i)
{
	t_mat4	t;
	float	det;
	int j;

	m4_inverse1(&t, i);
	m4_inverse2(&t, i);
	det = i.m[0] * t.m[0] + i.m[1] * t.m[4] + i.m[2] * t.m[8] + i.m[3] * t.m[12];
	if (det == 0)
		return m4_zero();
	det = 1.0 / det;
	j = 0;
	while (j < 16)
	{
		t.m[j] = t.m[j] * det;
		j++;
	}
	return (t);
}

t_mat4	m4_transpose(t_mat4 in)
{
	int		x;
	int		z;
	t_mat4	out;

	z = 0;
	while(z < 4)
	{
		x = 0;
		while(x < 4)
		{
			out.m[(z * 4) + x] = in.m[(x * 4) + z];
			x++;
		}
		z++;
	}
	return (out);
}