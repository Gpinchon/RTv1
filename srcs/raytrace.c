/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 21:25:32 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/24 21:51:07 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

float	compute_attenuation(t_light l, t_vec3 data[4])
{
	float	att;

	if (l.type == DIRECTIONAL)
		return (l.power);
	att = 1 / pow(fmax(vec3_distance(l.position, data[0]) - l.falloff, 0)
		/ l.falloff + 1, 2) * l.power;
	return ((att - l.attenuation) / (1 - l.attenuation));
}

t_rgb	compute_illumination(t_primitive p, t_light l, t_vec3 data[4])
{
	t_rgb		c;
	float		diff;
	float		spec;
	float		att;

	diff = DIFFUSE(data[3], data[2], data[1], p.material);
	if (l.type == SPOT)
		diff *= vec3_dot(vec3_normalize(l.direction),
		vec3_negate(data[1])) > cos(TO_RADIAN(l.spot_size / 2.0)) ? 1 : 0;
	c = rgba_to_rgb(p.material.ambient);
	if (diff > 0)
	{
		spec = SPECULAR(data[3], data[2], data[1],
			p.material.spec_power) * (1 - p.material.roughness) * l.specular;
		att = compute_attenuation(l, data);
		c = rgb_add(c, rgb_scale(rgb_divide(rgb_add(l.color,
			rgba_to_rgb(p.material.diffuse)), 1), diff));
		c = (spec > 0 && att > 0) ? rgb_add(c, rgb_scale(rgb_multiply(l.color,
			rgba_to_rgb(p.material.specular)), spec)) : c;
		c = rgb_scale(c, att);
	}
	return (c);
}

t_rgb	point_color(t_rt rt, t_primitive p, t_light l, float *z)
{
	t_vec3		pos;
	t_vec3		light_dir;
	t_vec3		view_dir;
	t_rgb		co;

	pos = (t_vec3){
		(rt.scene.camera.ray.origin.x + rt.scene.camera.ray.direction.x * *z),
		(rt.scene.camera.ray.origin.y + rt.scene.camera.ray.direction.y * *z),
		(rt.scene.camera.ray.origin.z + rt.scene.camera.ray.direction.z * *z)};
	light_dir = compute_lightdir(l, pos);
	view_dir = vec3_normalize(vec3_substract(rt.scene.camera.ray.origin, pos));
	co = compute_illumination(p, l,
		(t_vec3[]){pos, light_dir, view_dir, rt.normal[p.type](pos, p)});
	return ((t_rgb){clamp(co.r, 0, 1), clamp(co.g, 0, 1), clamp(co.b, 0, 1)});
}

t_ray	generate_shadow_ray(t_camera c, t_light l, float z)
{
	t_ray	ray;

	ray.origin = (t_vec3){
		(c.ray.origin.x + c.ray.direction.x * z),
		(c.ray.origin.y + c.ray.direction.y * z),
		(c.ray.origin.z + c.ray.direction.z * z)};
	ray.direction = l.type == DIRECTIONAL ? vec3_normalize(l.position)
		: vec3_normalize(vec3_substract(l.position, ray.origin));
	ray.origin = vec3_add(ray.origin, vec3_scale(ray.direction, 0.5));
	return (ray);
}

void	do_raytracer(t_point2 size, t_rt rt)
{
	t_point2	current;
	t_rgb		final_color;
	UINT		ss2;

	current.y = 0;
	ss2 = (SUPERSAMPLING) * (SUPERSAMPLING);
	while (current.y < size.y)
	{
		current.x = 0;
		while (current.x < size.x)
		{
			final_color = iterate_through_pixel(size, rt, current);
			final_color = rgb_divide(final_color, ss2);
			final_color = rgb_scale(final_color, 255);
			put_rgb_to_image(rt.image, current, final_color);
			current.x++;
		}
		current.y++;
	}
}
