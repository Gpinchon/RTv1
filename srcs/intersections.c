/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 17:24:49 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/23 13:40:07 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

enum e_bool	intersect_sphere(t_primitive s, t_ray r, float *current_z)
{
	t_vec3	eye;
	float	a;
	float	b;
	float	c;
	float	t[2];

	eye = vec3_substract(r.origin, s.position);
	a = vec3_dot(r.direction, r.direction);
	b = vec3_dot(eye, r.direction) * 2.0;
	c = vec3_dot(eye, eye) - (s.radius2);
	return (solve_quadratic(a, b, c, t) && test_intersect(t, current_z));
}

//a   = vec3_dot(ray.direction, ray.direction) - pow(vec3_dot(ray.direction, cp.direction), 2);
//b/2 = vec3_dot(ray.direction, eye) - vec3_dot(ray.direction, cp.direction) * vec3_dot(eye, cp.direction);
//c   = vec3_dot(eye, eye) - pow(vec3_dot(eye, cp.direction), 2) - cp.radius2;

enum e_bool intersect_cylinder(t_primitive cp, t_ray r, float *current_z)
{
	t_vec3	v[6];
	float	t[2];
	float	f[4];

	v[0] = vec3_project(cp.position, cp.direction);
	v[1] = vec3_substract(cp.position, v[0]);
	v[2] = vec3_project(r.origin, cp.direction);
	v[3] = vec3_project(r.direction, cp.direction);
	v[4] = vec3_substract(r.direction, v[3]);
	v[5] = vec3_substract(vec3_substract(r.origin, v[2]), v[1]);
	f[0] = vec3_dot(v[4], v[4]);
	f[1] = vec3_dot(v[5], v[4]) * 2.0;
	f[2] = vec3_dot(v[5], v[5]) - (cp.radius2);
	if ((f[3] = (f[1] * f[1]) - (4.0 * f[0] * f[2])) <= 0)
		return (false);
	f[3] = sqrt(f[3]);
	t[0] = (-f[1] - f[3]) / (2.0 * f[0]);
	t[1] = (-f[1] + f[3]) / (2.0 * f[0]);
	if (cp.size > 0 && vec3_length(vec3_substract(vec3_add(v[2],
		vec3_scale(v[3], t[0])), v[0])) >= cp.size / 2)
		t[0] = 0;
	if (cp.size > 0 && vec3_length(vec3_substract(vec3_add(v[2],
		vec3_scale(v[3], t[1])), v[0])) >= cp.size / 2)
		t[1] = 0;
	return (test_intersect(t, current_z));
}

enum e_bool	intersect_plane(t_primitive cp, t_ray r, float *current_z)
{
	t_vec3	normal;
	float	denom;
	float	t;

	normal = vec3_negate(cp.direction);
	denom = vec3_dot(normal, r.direction);
	if (denom > 1e-6)
	{
		t = vec3_dot(vec3_substract(cp.position, r.origin), normal) / denom;
		if (t >= 0
		&& (t <= *(current_z) || *(current_z) == -1))
		{
			*current_z = t;
			return (true);
		}
	}
	return (false);
}
