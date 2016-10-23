/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 16:00:22 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/24 16:35:19 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_mat4	m4_transpose(t_mat4 in)
{
	int		x;
	int		z;
	t_mat4	out;

	z = 0;
	while (z < 4)
	{
		x = 0;
		while (x < 4)
		{
			out.m[(z * 4) + x] = in.m[(x * 4) + z];
			x++;
		}
		z++;
	}
	return (out);
}
