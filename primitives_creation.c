/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives_creation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 18:48:34 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 20:26:44 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_primitive	new_sphere(t_vec3 position, float radius)
{
	t_primitive	p;

	p.radius = radius;
	p.radius2 = p.radius * p.radius;
	p.position = position;
	p.type = SPHERE;
	return (p);
}

t_primitive	new_cylinder(t_vec3 pos, t_vec3 dir, float radius, float size)
{
	t_primitive	p;

	p.radius = radius;
	p.radius2 = p.radius * p.radius;
	p.size = size;
	p.position = pos;
	p.direction = dir;
	p.type = CYLINDER;
	return (p);
}

t_primitive	new_cone(t_vec3 pos, t_vec3 dir, float radius, float size)
{
	t_primitive	p;

	p.radius = TO_RADIAN(radius);
	p.radius2 = p.radius * p.radius;
	p.size = size;
	p.position = pos;
	p.direction = dir;
	p.type = CONE;
	return (p);
}

t_primitive	new_plane(t_vec3 position, t_vec3 direction)
{
	t_primitive	p;

	p.position = position;
	p.direction = direction;
	p.type = PLANE;
	return (p);
}
