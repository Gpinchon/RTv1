/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 19:24:51 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 21:07:10 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

/*
** lookat - position	-> create view vector
** v * up				-> find right vector
** r * v				-> orthogonalise up vector
** r * tan(vfov / 2.0)
** u * tan(vfov / 2.0)	-> scale up and right vectors
** v - r + u			-> adjust for image space normalisation
** d.x == FOV
** d.y == ASPECT RATIO
*/

t_camera	new_camera(t_vec3 position, t_vec3 lookat, t_vec3 up, t_vec2 d)
{
	t_camera	gopro;
	t_vec3		v;
	t_vec3		r;
	t_vec3		u;

	v = vec3_substract(lookat, position);
	r = vec3_normalize(vec3_cross(v, up));
	u = vec3_normalize(vec3_cross(r, v));
	v = vec3_substract(v,
		vec3_add(r = vec3_scale(r, tan(d.x / 2.0) * d.y),
		u = vec3_scale(u, tan(d.x / 2.0) * d.y)));
	gopro.transform = (t_mat3){.m = {
		r.x * 2, r.y * 2, r.z * 2,
		u.x * 2, u.y * 2, u.z * 2,
		v.x, v.y, v.z
	}};
	gopro.position = position;
	gopro.lookat = lookat;
	gopro.up = up;
	gopro.fov = d.x;
	return (gopro);
}

t_camera	update_camera(t_camera gopro, float aspect)
{
	t_vec3	v;
	t_vec3	r;
	t_vec3	u;
	float	fov;

	v = vec3_substract(gopro.lookat, gopro.position);
	r = vec3_normalize(vec3_cross(v, gopro.up));
	u = vec3_normalize(vec3_cross(r, v));
	fov = tan(gopro.fov / 2.0) * aspect;
	v = vec3_substract(v,
		vec3_add(r = vec3_scale(r, fov),
		u = vec3_scale(u, fov)));
	gopro.transform = (t_mat3){.m = {
		r.x * 2, r.y * 2, r.z * 2,
		u.x * 2, u.y * 2, u.z * 2,
		v.x, v.y, v.z
	}};
	return (gopro);
}

t_ray		generate_ray(t_camera gopro, float x, float y)
{
	t_ray	ray;

	ray.origin = gopro.position;
	ray.direction = m3_mult_vec3(gopro.transform,
					new_vec3(x, y, 1));
	return (ray);
}
