# include <rt.h>
# include <stdio.h>
# define	SUPERSAMPLING	4
# define	SPHERE		0
# define	CYLINDER	1
# define	CONE		3
# define	PLANE		4

double		*get_current_z(t_depth_buffer *depth,
	t_point2 screen_size, t_point2 current)
{
	return (&depth->buffer
		[(int)floor(depth->size.x / (float)screen_size.x * current.x)]
		[(int)floor(depth->size.y / (float)screen_size.y * current.y)]);
}

void	do_raytracer(t_point2 screen_size, t_rt rt)
{
	t_point2	current;
	t_vec2		current_float;
	t_primitive	p;
	t_light		l;
	t_rgb		final_color;
	t_camera	c;

	c.direction = (t_vec3){0.001, 0.001, 1};
	c.position = (t_vec3){0, 0, -1000};
	p.position = (t_vec3){0, 0, 0};
	p.direction = (t_vec3){-1, -1, 0};
	p.type =  CYLINDER;
	p.radius = 100;
	p.size = 500;
	p.material.diffuse = (t_rgba){1, 0, 0, 1};
	p.material.ambient = (t_rgba){0, 0, 0, 1};
	p.material.specular = (t_rgba){1, 1, 1, 1};
	p.material.spec_power = 30;
	p.material.roughness = 1;
	p.material.albedo = 1;
	l.type = POINT;
	l.direction	= (t_vec3){0.5, -0.5, 1};
	l.position = (t_vec3){-100, 100, -250};
	l.color = (t_rgb){1, 1, 1};
	l.power = 1;
	l.attenuation = 0.002;
	l.falloff = 200;
	l.spot_size = 45;
	current.y = 0;
	while (current.y < screen_size.y)
	{
		current.x = 0;
		while (current.x < screen_size.x)
		{
			current_float.y = current.y;
			final_color = (t_rgb){0, 0, 0};
			double		*current_z;
			current_z = get_current_z(rt.depth, screen_size, current);
			while (current_float.y < current.y + 1)
			{
				current_float.x = current.x;
				while (current_float.x < current.x + 1)
				{
					t_vec2 coord = (t_vec2){screen_size.x / 2.0 - current_float.x, screen_size.y / 2.0 - current_float.y};
					c.ray.origin = (t_vec3){c.position.x + coord.x, c.position.y + coord.y, c.position.z};
					c.ray.direction = vec3_normalize(c.direction);
					t_rgb color = rgb_divide(get_image_color(rt.image, current), 255);
					if ((p.type == SPHERE && intersect_sphere(p, c.ray, current_z))
					|| (p.type == CYLINDER && intersect_cylinder(p, c.ray, current_z))
					|| (p.type == CONE && intersect_cone(p, c.ray, current_z))
					|| (p.type == PLANE && intersect_plane(p, c.ray, current_z)))
					{
						t_vec3		normal = p.direction;
						t_vec3		position;
						t_vec3		light_dir;
						t_vec3		view_dir;
						position.x = (c.ray.origin.x + c.ray.direction.x * *current_z);
						position.y = (c.ray.origin.y + c.ray.direction.y * *current_z);
						position.z = (c.ray.origin.z + c.ray.direction.z * *current_z);
						if (p.type == CYLINDER)
							normal = vec3_normalize((t_vec3){
								(position.x - p.position.x) / p.radius,
								0,
								(position.z - p.position.z) / p.radius
							});
						else if (p.type == SPHERE || p.type == PLANE)
							normal = vec3_normalize((t_vec3){
								(position.x - p.position.x) / p.radius,
								(position.y - p.position.y) / p.radius,
								(position.z - p.position.z) / p.radius
							});
						else if (p.type == CONE)
							normal = vec3_normalize((t_vec3){
								(position.x - p.position.x),
								0,
								(position.z - p.position.z)
							});
						light_dir = compute_lightdir(l, position);
						view_dir = vec3_normalize(vec3_substract(c.ray.origin, position));
						double	diffuse = DIFFUSE(normal, view_dir, light_dir, p.material);
						if (l.type == SPOT)
						{
							float dotAngle = vec3_dot(vec3_normalize(l.direction), vec3_negate(light_dir));
							diffuse *= dotAngle > cos(TO_RADIAN(l.spot_size / 2.0)) ? 1 : 0;
						}
						color = rgba_to_rgb(p.material.ambient);
						if (diffuse > 0)
						{
							float specular = SPECULAR(normal, view_dir, light_dir, p.material.spec_power / (1 + p.material.roughness));
							float d = fmax(vec3_distance(l.position, position) - l.falloff, 0);
							float attenuation = 1 / pow(d / l.falloff + 1, 2) * l.power;
							attenuation = (attenuation - l.attenuation) / (1 - l.attenuation);
							color = rgb_add(color, rgb_scale(rgb_multiply(l.color, rgba_to_rgb(p.material.diffuse)), diffuse));
							if (specular > 0 && attenuation > 0)
								color = rgb_add(color, rgb_scale(rgba_to_rgb(p.material.specular), specular));
							color = rgb_scale(color, attenuation);
							color.r = clamp(color.r, 0, 1);
							color.g = clamp(color.g, 0, 1);
							color.b = clamp(color.b, 0, 1);
						}
					}
					final_color = rgb_add(final_color, color);
					current_float.x += 1 / ((float)SUPERSAMPLING);
				}
				current_float.y += 1 / ((float)SUPERSAMPLING);
			}
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

int main()
{
	printf("%lu, %lu\n", PRIMITIVE, LIGHT);
	t_rt	rt;
	rt.framework = init_mlx_framework();
	rt.window = new_window(rt.framework, WIDTH, HEIGHT, "RTv1");
	rt.image = new_image(rt.framework, WIDTH, HEIGHT, "display");
	rt.depth = new_depth_buffer((t_point2){512, 512});
	fill_image(rt.image, (t_rgb){127, 127, 127});
	do_raytracer((t_point2){WIDTH, HEIGHT}, rt);
	rt.depth = destroy_depth_buffer(rt.depth);
	attach_image_to_window(rt.image, rt.window);
	loop_callback(rt.framework, refresh_window, rt.window);
	init_loop(rt.framework);
	return 0;
}