# include <rt.h>
# include <stdio.h>
# define	SUPERSAMPLING	2
# define	SPHERE		0x0
# define	CYLINDER	0x1
# define	CONE		0x3
# define	PLANE		0x4

double		*get_current_z(t_depth_buffer *depth,
	t_point2 screen_size, t_point2 current)
{
	return (&depth->buffer
		[(int)floor(depth->size.x / (float)screen_size.x * current.x)]
		[(int)floor(depth->size.y / (float)screen_size.y * current.y)]);
}

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
	if (p.type == CYLINDER)
	{
		float len = vec3_length(vec3_substract(position, c.ray.origin));
		float m = vec3_dot(c.ray.direction, p.direction) * len;
		m += vec3_dot(vec3_substract(c.ray.origin, p.position), p.direction);
		normal = vec3_substract(position, p.position);
		normal = vec3_normalize(vec3_substract(normal, vec3_fscale(p.direction, m)));
		//normal = vec3_normalize(vec3_cross((t_vec3){
		//	(position.x - p.position.x) / p.radius,
		//	(position.y - p.position.y) / p.radius,
		//	(position.z - p.position.z) / p.radius}, p.direction));
	}
	else if (p.type == SPHERE)
		normal = vec3_normalize((t_vec3){
			(position.x - p.position.x) / p.radius,
			(position.y - p.position.y) / p.radius,
			(position.z - p.position.z) / p.radius
		});
	else if (p.type == PLANE)
		normal = vec3_normalize(p.direction);
	else if (p.type == CONE)
		normal = vec3_fdivide(vec3_normalize((t_vec3){
					(position.x - p.position.x), 0,
					(position.z - p.position.z)
				}), p.radius);
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
		color = rgb_add(color, rgb_scale(rgb_divide(rgb_add(l.color, rgba_to_rgb(p.material.diffuse)), 1), diffuse));
		if (specular > 0 && attenuation > 0)
			color = rgb_add(color, rgb_scale(rgb_multiply(l.color, rgba_to_rgb(p.material.specular)), specular));
		color = rgb_scale(color, attenuation);
		color.r = clamp(color.r, 0, 1);
		color.g = clamp(color.g, 0, 1);
		color.b = clamp(color.b, 0, 1);
	}
	return (color);
}

void	do_raytracer(t_point2 size, t_rt rt)
{
	t_point2	current;
	t_primitive	p;
	t_light		l;
	t_rgb		final_color;
	t_camera	c;

	c.direction = (t_vec3){0, 0, 1};
	c.position = (t_vec3){10, 10, -500};
	p.position = (t_vec3){0, 0, 0};
	p.direction = (t_vec3){-1, -1, 0};
	p.type = CYLINDER;
	p.radius = 100;
	p.size = 200;
	p.material.diffuse = (t_rgba){0, 1, 1, 1};
	p.material.ambient = (t_rgba){0, 0, 0, 1};
	p.material.specular = (t_rgba){1, 1, 1, 1};
	p.material.spec_power = 80;
	p.material.roughness = 0.5;
	p.material.albedo = 1;
	l.type = POINT;
	l.direction	= (t_vec3){0.5, -0.5, 200};
	l.position = (t_vec3){-100, 100, -250};
	l.color = (t_rgb){1, 1, 1};
	l.power = 1;
	l.attenuation = 0.002;
	l.falloff = 200;
	l.spot_size = 45;
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
			while (fcur.y < current.y + 1)
			{
				fcur.x = current.x;
				while (fcur.x < current.x + 1)
				{
					//t_vec2 coord = (t_vec2){size.x / 2.0 - fcur.x, size.y / 2.0 - fcur.y};
					//c.ray.origin = (t_vec3){
					//	c.position.x + coord.x,
					//	c.position.y + coord.y,
					//	c.position.z};
					//c.ray.direction = vec3_normalize(c.direction);
					float fovx = TO_RADIAN(30);
					float fovy = (float)size.y / (float)size.x * fovx;
					t_vec2	coord = (t_vec2){(size.x - 2 * fcur.x) / size.x, (size.y - 2 * fcur.y) / size.y};
					c.ray.origin = (t_vec3){
						c.position.x,
						c.position.y,
						c.position.z};
					c.ray.direction = (t_vec3){
						c.direction.x + coord.x * tan(fovx),
						c.direction.y + coord.y * tan(fovy),
						c.direction.z
					};
					t_rgb color = rgb_divide(get_image_color(rt.image, current), 255);
					if ((p.type == SPHERE && intersect_sphere(p, c.ray, current_z))
					|| (p.type == CYLINDER && intersect_cylinder(p, c.ray, current_z))
					|| (p.type == CONE && intersect_cone(p, c.ray, current_z))
					|| (p.type == PLANE && intersect_plane(p, c.ray, current_z)))
					{
						color = compute_point_color(p, c, l, current_z);
					}
					final_color = rgb_add(final_color, color);
					fcur.x += 1 / ((float)SUPERSAMPLING);
				}
				fcur.y += 1 / ((float)SUPERSAMPLING);
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