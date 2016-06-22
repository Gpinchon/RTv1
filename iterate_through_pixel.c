/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_through_pixel.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 21:20:41 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 21:24:04 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static enum e_bool	in_shadow(t_rt rt, t_light l, double z)
{
	t_ray	shadow_ray;
	float	fake_z;
	int		k;

	k = 0;
	while (k < rt.scene.primitive_nbr)
	{
		shadow_ray = generate_shadow_ray(rt.scene.camera, l, z);
		fake_z = vec3_distance(l.position, shadow_ray.origin);
		if (rt.intersect[rt.scene.primitive[k].type](rt.scene.primitive[k],
		shadow_ray, &fake_z))
			return (true);
		k++;
	}
	return (false);
}

static void			iterate_through_lights(t_rt rt, t_point2 o,
	t_rgb *c, float *z)
{
	while (o.y < rt.scene.light_nbr)
	{
		if (!in_shadow(rt, rt.scene.light[o.y], *z))
			*(c) = o.y > 0 ? rgb_add(*(c),
			point_color(rt, rt.scene.primitive[o.x],
		rt.scene.light[o.y], z)) : point_color(rt,
		rt.scene.primitive[o.x], rt.scene.light[o.y], z);
		else
			*(c) = o.y > 0 ? rgb_add(*(c),
	rgba_to_rgb(rt.scene.primitive[o.x].material.ambient)) :
		rgba_to_rgb(rt.scene.primitive[o.x].material.ambient);
		o.y++;
	}
}

static float		iterate_through_primitives(t_rt rt, t_point2 obj,
	t_rgb *color)
{
	float		z;
	t_scene		s;
	t_primitive	p;

	z = -1;
	s = rt.scene;
	while (obj.x < s.primitive_nbr)
	{
		p = s.primitive[obj.x];
		if (rt.intersect[p.type](p, s.camera.ray, &z))
		{
			obj.y = 0;
			iterate_through_lights(rt, obj, color, &z);
			z = (z + z) * 0.5;
		}
		obj.x++;
	}
	return (z);
}

static void			assign_depth(t_point2 size, t_point2 current,
	t_rt rt, float z)
{
	if (z != -1)
		*(get_current_z(rt.depth, size, current)) = z;
}

t_rgb				iterate_through_pixel(t_point2 size, t_rt rt,
	t_point2 current)
{
	t_vec2		fcur;
	t_rgb		c[2];
	float		z;
	t_point2	obj;

	fcur.y = current.y;
	c[1] = (t_rgb){0, 0, 0};
	while (fcur.y < current.y + 1)
	{
		fcur.x = current.x;
		while (fcur.x < current.x + 1)
		{
			obj.x = 0;
			rt.scene.camera.ray = generate_ray(rt.scene.camera,
				(size.x - 2 * fcur.x), (size.y - 2 * fcur.y));
			c[0] = BACKGROUND;
			z = iterate_through_primitives(rt, obj, &c[0]);
			c[1] = rgb_add(c[1], (t_rgb){c[0].r > 1 ? 1 :
			c[0].r, c[0].g > 1 ? 1 : c[0].g, c[0].b > 1 ? 1 : c[0].b});
			fcur.x += 1 / ((float)SUPERSAMPLING);
		}
		fcur.y += 1 / ((float)SUPERSAMPLING);
	}
	assign_depth(size, current, rt, z);
	return (c[1]);
}
