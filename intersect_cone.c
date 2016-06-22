/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 21:03:57 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 21:12:06 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static float	cone_factor1(t_primitive cp, t_ray r, t_vec3 *vec)
{
	return (pow(cos(cp.radius), 2) * vec3_dot(vec[1], vec[1]) -
		pow(sin(cp.radius), 2) * pow(vec3_dot(r.direction, cp.direction), 2));
}

static float	cone_factor2(t_primitive cp, t_ray r, t_vec3 *vec)
{
	return (2 * (pow(cos(cp.radius), 2) * vec3_dot(vec[1], vec[2])) -
		2 * (pow(sin(cp.radius), 2) * vec3_dot(r.direction, cp.direction)
		* vec3_dot(vec[0], cp.direction)));
}

static float	cone_factor3(t_primitive cp, t_vec3 *vec)
{
	return (pow(cos(cp.radius), 2) * vec3_dot(vec[2], vec[2]) -
	pow(sin(cp.radius), 2) * pow(vec3_dot(vec[0], cp.direction), 2));
}

enum e_bool		intersect_cone(t_primitive cp, t_ray r, float *current_z)
{
	float	z;
	float	t[2];
	t_vec3	vec[3];

	vec[0] = vec3_substract(r.origin, cp.position);
	vec[1] = vec3_substract(r.direction, vec3_scale(cp.direction,
		vec3_dot(r.direction, cp.direction)));
	vec[2] = vec3_substract(vec[0], vec3_scale(cp.direction,
		vec3_dot(vec[0], cp.direction)));
	z = *(current_z);
	if (solve_quadratic(cone_factor1(cp, r, vec),
		cone_factor2(cp, r, vec),
		cone_factor3(cp, vec), t) && (test_intersect(t, &z)))
	{
		if ((cp.size == 0 || cp.direction.x > 0)
		|| (cp.size > 0. && vec3_dot(cp.direction,
			vec[0] = vec3_substract(vec3_add(r.origin,
			vec3_scale(r.direction, z)), cp.position)) > 0.
		&& cp.size / cos(atan(cp.radius)) > vec3_length(vec[0])))
		{
			*(current_z) = z;
			return (true);
		}
	}
	return (false);
}
