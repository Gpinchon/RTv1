# include <rt.h>
# include <stdio.h>
# define	SUPERSAMPLING	2

double		*get_current_z(t_depth_buffer *depth,
	t_point2 screen_size, t_point2 current)
{
	return (&depth->buffer
		[(int)floor(depth->size.x / (float)screen_size.x * current.x)]
		[(int)floor(depth->size.y / (float)screen_size.y * current.y)]);
}

//t_rgb	compute_illumination()
//{
//	
//}

t_rgb	compute_point_color(t_primitive p, t_camera c, t_light l, double *current_z)
{
	t_vec3		normal = p.direction;
	t_vec3		position;
	t_vec3		light_dir;
	t_vec3		view_dir;
	t_rgb		color;

	position.x = (c.ray.origin.x + c.ray.direction.x * *current_z);
	position.y = (c.ray.origin.y + c.ray.direction.y * *current_z);
	position.z = (c.ray.origin.z + c.ray.direction.z * *current_z);
	normal = p.normal(position, p);
	light_dir = compute_lightdir(l, position);
	view_dir = vec3_normalize(vec3_substract(c.ray.origin, position));
	double	diffuse = DIFFUSE(normal, view_dir, light_dir, p.material);
	if (l.type == SPOT)
		diffuse *= vec3_dot(vec3_normalize(l.direction),
		vec3_negate(light_dir)) > cos(TO_RADIAN(l.spot_size / 2.0)) ? 1 : 0;
	color = rgba_to_rgb(p.material.ambient);
	if (diffuse > 0)
	{
		float specular = SPECULAR(normal, view_dir, light_dir, p.material.spec_power) * (1 - p.material.roughness);
		float d = fmax(vec3_distance(l.position, position) - l.falloff, 0);
		float attenuation = 1;
		if (l.type != DIRECTIONAL)
		{
			attenuation = 1 / pow(d / l.falloff + 1, 2) * l.power;
			attenuation = (attenuation - l.attenuation) / (1 - l.attenuation);
		}
		color = rgb_add(color, rgb_scale(rgb_divide(rgb_add(l.color, rgba_to_rgb(p.material.diffuse)), 1), diffuse));
		if (specular > 0 && attenuation > 0)
			color = rgb_add(color, rgb_scale(rgb_multiply(l.color, rgba_to_rgb(p.material.specular)), specular));
		color = rgb_scale(color, attenuation);
	}
	return ((t_rgb){clamp(color.r, 0, 1), clamp(color.g, 0, 1), clamp(color.b, 0, 1)});
}

t_vec3				vec3_rotx(const t_vec3 vec, const double r)
{
	double			cos_r;
	double			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = vec.x;
	ret.y = cos_r * vec.y - sin_r * vec.z;
	ret.z = sin_r * vec.y + cos_r * vec.z;
	return (ret);
}

t_vec3				vec3_roty(const t_vec3 vec, const double r)
{
	double			cos_r;
	double			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = sin_r * vec.z + cos_r * vec.x;
	ret.y = vec.y;
	ret.z = cos_r * vec.z - sin_r * vec.x;
	return (ret);
}

t_vec3				vec3_rotz(const t_vec3 vec, const double r)
{
	double			cos_r;
	double			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = cos_r * vec.x - sin_r * vec.y;
	ret.y = sin_r * vec.x + cos_r * vec.y;
	ret.z = vec.z;
	return (ret);
}

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

t_camera	update_camera(t_camera gopro, double aspect)
{
	t_vec3		v;
	t_vec3		r;
	t_vec3		u;

	v = vec3_substract(gopro.lookat, gopro.position);
	r = vec3_normalize(vec3_cross(v, gopro.up));
	u = vec3_normalize(vec3_cross(r, v));
	v = vec3_substract(v,
		vec3_add(r = vec3_scale(r, tan(gopro.fov / 2.0) * aspect),
		u = vec3_scale(u, tan(gopro.fov / 2.0) * aspect)));
	gopro.transform = (t_mat3){.m = {
		r.x * 2, r.y * 2, r.z * 2,
		u.x * 2, u.y * 2, u.z * 2,
		v.x, v.y, v.z
	}};
	return (gopro);
}

t_ray	generate_ray(t_camera gopro, float x, float y)
{
	t_ray ray;

	ray.origin = gopro.position;
	ray.direction = vec3_normalize(m3_mult_vec3(gopro.transform,
					vec3_normalize(new_vec3(x, y, 1))));
	return (ray);
}

void	do_raytracer(t_point2 size, t_rt rt)
{
	t_point2	current;
	t_primitive	p[2];
	t_light		l;
	t_rgb		final_color;
	t_camera	c;

	//c.direction = (t_vec3){0, 0, 1};
	//c.position = (t_vec3){0, 0, -500};
	c = new_camera((t_vec3){-500, 250, -500}, (t_vec3){0, 0, 0}, (t_vec3){0, 1, 0}, (t_vec2){TO_RADIAN(45), (float)size.y / (float)size.x});
	p[0] = new_sphere((t_vec3){0, 0, 0}, 250);
	p[1] = new_plane((t_vec3){0, 0, 0}, (t_vec3){-1, 1, 0});
	p[0].material.diffuse = (t_rgba){0, 0, 1, 1};
	p[0].material.ambient = (t_rgba){0, 0, 0, 1};
	p[0].material.specular = (t_rgba){1, 1, 1, 1};
	p[0].material.spec_power = 30;
	p[0].material.roughness = 0;
	p[0].material.albedo = 1;
	p[1].material.diffuse = (t_rgba){0, 1, 1, 1};
	p[1].material.ambient = (t_rgba){0, 0, 0, 1};
	p[1].material.specular = (t_rgba){1, 1, 1, 1};
	p[1].material.spec_power = 30;
	p[1].material.roughness = 0;
	p[1].material.albedo = 1;
	l.type = POINT;
	l.direction	= (t_vec3){0.5, -0.5, 0};
	l.position = (t_vec3){-250, 250, -250};
	l.color = (t_rgb){1, 1, 1};
	l.power = 1;
	l.attenuation = 0.002;
	l.falloff = 200;
	l.spot_size = 90;
	current.y = 0;
	while (current.y < size.y)
	{
		current.x = 0;
		while (current.x < size.x)
		{
			t_vec2		fcur;
			double		*current_z;
			fcur.y = current.y;
			final_color = (t_rgb){0, 0, 0};
			current_z = get_current_z(rt.depth, size, current);
			double z = -1;
			while (fcur.y < current.y + 1)
			{
				fcur.x = current.x;
				while (fcur.x < current.x + 1)
				{
					int i = 0;
					c.ray = generate_ray(c, (size.x - 2 * fcur.x), (size.y - 2 * fcur.y));
					t_rgb color = rgb_divide(get_image_color(rt.image, current), 255);
					z = -1;
					while (i < 2)
					{
						if (p[i].intersect(p[i], c.ray, &z))
						{
							color = compute_point_color(p[i], c, l, &z);
							z = (z + z) / 2.0;
						}
						i++;
					}
					final_color = rgb_add(final_color, color);
					fcur.x += 1 / ((float)SUPERSAMPLING);
				}
				fcur.y += 1 / ((float)SUPERSAMPLING);
			}
			if (z != -1)
				*(current_z) = z;
			final_color = rgb_divide(final_color, (SUPERSAMPLING) * (SUPERSAMPLING));
			final_color = rgb_scale(final_color, 255);
			put_rgb_to_image(rt.image, current, final_color);
			current.x++;
		}
		current.y++;
	}
	printf("done\n");
}

t_depth_buffer	*new_depth_buffer(t_point2 size)
{
	t_depth_buffer *n;

	n = ft_memalloc(sizeof(t_depth_buffer));
	n->size = size;
	n->buffer = ft_memalloc(sizeof(double) * size.x);
	while (size.x)
	{
		n->buffer[size.x - 1] = ft_memalloc(sizeof(double) * n->size.y);
		while (size.y)
		{
			n->buffer[size.x - 1][size.y - 1] = -1;
			size.y--;
		}
		size.y = n->size.y;
		size.x--;
	}
	return (n);
}

void		*destroy_depth_buffer(t_depth_buffer *d)
{
	if (!d || !d->buffer)
		return d;
	while (d->size.x)
	{
		if (d->buffer[d->size.x - 1])
			free(d->buffer[d->size.x - 1]);
		d->size.x--;
	}
	free(d->buffer);
	free(d);
	return (NULL);
}

int	check_key(int key, t_rt *rt)
{
	if (key == 53 || key == 65307)
	{
		destroy_framework(rt->framework);
		destroy_depth_buffer(rt->depth);
		exit(0);
	}
	return(0);
}

int main()
{
	t_rt	rt;
	rt.framework = init_mlx_framework();
	rt.window = new_window(rt.framework, WIDTH, HEIGHT, "RTv1");
	rt.image = new_image(rt.framework, WIDTH, HEIGHT, "display");
	rt.depth = new_depth_buffer((t_point2){512, 512});
	attach_image_to_window(rt.image, rt.window);
	fill_image(rt.image, (t_rgb){127, 127, 127});
	refresh_window(rt.window);
	key_callback(rt.window, check_key, &rt);
	loop_callback(rt.framework, refresh_window, rt.window);
	do_raytracer((t_point2){WIDTH, HEIGHT}, rt);
	rt.depth = destroy_depth_buffer(rt.depth);
	init_loop(rt.framework);
	return (0);
}