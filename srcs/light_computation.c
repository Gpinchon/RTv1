/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_computation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 19:00:12 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 20:23:57 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

float	trowbridge_reitz_specular(t_vec3 n, t_vec3 eye, t_vec3 l, float s)
{
	return (pow(1 / (1 + (1 - pow(vec3_dot(n,
		vec3_normalize(vec3_add(l, eye))), 2)) * s), 2));
}

float	blinn_phong_specular(t_vec3 n, t_vec3 eye, t_vec3 l, float s)
{
	return (pow(vec3_dot(vec3_normalize(vec3_add(l, eye)), n), s));
}

float	oren_nayar_diffuse(t_vec3 n, t_vec3 eye, t_vec3 l, t_mtl mtl)
{
	float	f[7];

	f[0] = vec3_dot(l, n);
	f[1] = vec3_dot(n, eye);
	f[2] = vec3_dot(l, eye) - f[0] * f[1];
	f[3] = float_lerp(1.0, fmax(f[0], f[1]), float_step(0.0, f[2]));
	f[4] = mtl.roughness * mtl.roughness;
	f[5] = 1.0 + f[4] * (mtl.albedo / (f[4] + 0.13) + 0.5 / (f[4] + 0.33));
	f[6] = 0.45 * f[4] / (f[4] + 0.09);
	return (clamp(mtl.albedo * fmax(0.0, f[0]) * (f[5] + f[6] *
		f[2] / f[3]) / M_PI, 0, 1));
}

float	lambert_diffuse(t_vec3 n, t_vec3 eye, t_vec3 l, t_mtl mtl)
{
	return (clamp(mtl.albedo * vec3_dot(n, l) + mtl.roughness, 0, 1));
	(void)eye;
}

t_vec3	compute_lightdir(t_light l, t_vec3 position)
{
	if (l.type == POINT || l.type == SPOT)
		return (vec3_normalize(vec3_substract(l.position, position)));
	else if (l.type == DIRECTIONAL)
		return (vec3_normalize(l.position));
	return (vec3_normalize(l.position));
}
