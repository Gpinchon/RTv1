/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 16:03:20 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/24 16:06:42 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../adv_math.h"

t_mat4	m4_lookat(t_vec3 eye, t_vec3 target, t_vec3 up)
{
	t_mat4	out;
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;

	z = vec3_normalize(vec3_substract(target, eye));
	x = vec3_normalize(vec3_cross(z, up));
	y = vec3_cross(x, z);
	out.m[0] = x.x;
	out.m[1] = y.x;
	out.m[2] = -z.x;
	out.m[3] = 0.0;
	out.m[4] = x.y;
	out.m[5] = y.y;
	out.m[6] = -z.y;
	out.m[7] = 0.0;
	out.m[8] = x.z;
	out.m[9] = y.z;
	out.m[10] = -z.z;
	out.m[11] = 0.0;
	out.m[12] = -vec3_dot(x, eye);
	out.m[13] = -vec3_dot(y, eye);
	out.m[14] = vec3_dot(z, eye);
	out.m[15] = 1.0;
	return (out);
}

t_mat4	m4_persp(float fov, float aspect, float znear, float zfar)
{
	t_mat4	out;
	float	r;
	float	deltaz;
	float	cotangent;

	r = TO_RADIAN(fov / 2.0);
	deltaz = zfar - znear;
	cotangent = cos(r) / sin(r);
	out = m4_zero();
	out.m[0] = cotangent / aspect;
	out.m[5] = cotangent;
	out.m[10] = -(zfar + znear) / deltaz;
	out.m[11] = -1;
	out.m[14] = -2 * znear * zfar / deltaz;
	out.m[15] = 0;
	return (out);
}

t_mat4	m4_ortho(t_vec4 frustum, float znear, float zfar)
{
	t_mat4	out;
	float	tx;
	float	ty;
	float	tz;

	tx = -((frustum.x + frustum.y) / (frustum.x - frustum.y));
	ty = -((frustum.z + frustum.w) / (frustum.z - frustum.w));
	tz = -((zfar + znear) / (zfar - znear));
	out = m4_identity();
	out.m[0] = 2 / (frustum.x - frustum.y);
	out.m[5] = 2 / (frustum.z - frustum.w);
	out.m[10] = -2 / (zfar - znear);
	out.m[12] = tx;
	out.m[13] = ty;
	out.m[14] = tz;
	return (out);
}
