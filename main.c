/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 20:46:53 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 17:25:14 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rt.h>
# include <stdio.h>
# include <assert.h>
# define	SUPERSAMPLING	1
# define	WIDTH		512
# define	HEIGHT		512

float		*get_current_z(t_depth_buffer *depth,
	t_point2 screen_size, t_point2 current)
{
	return (&depth->buffer
		[(int)floor(depth->size.x / screen_size.x * current.x)]
		[(int)floor(depth->size.y / screen_size.y * current.y)]);
}

t_rgb	compute_illumination(t_primitive p, t_light l, t_vec3 data[4])
{
	t_rgb		c;
	float		diff;
	float		spec;
	float 		att;

	diff = DIFFUSE(data[3], data[2], data[1], p.material);
	if (l.type == SPOT)
		diff *= vec3_dot(vec3_normalize(l.direction),
		vec3_negate(data[1])) > cos(TO_RADIAN(l.spot_size / 2.0)) ? 1 : 0;
	c = rgba_to_rgb(p.material.ambient);
	if (diff > 0)
	{
		spec = SPECULAR(data[3], data[2], data[1],
			p.material.spec_power) * (1 - p.material.roughness) * l.specular;
		att = l.power;
		if (l.type != DIRECTIONAL)
		{
			att = 1 / pow(fmax(vec3_distance(l.position, data[0]) - l.falloff, 0)
				/ l.falloff + 1, 2) * l.power;
			att = (att - l.attenuation) / (1 - l.attenuation);
		}
		c = rgb_add(c, rgb_scale(rgb_divide(rgb_add(l.color,
			rgba_to_rgb(p.material.diffuse)), 1), diff));
		c = (spec > 0 && att > 0) ? rgb_add(c, rgb_scale(rgb_multiply(l.color,
			rgba_to_rgb(p.material.specular)), spec)) : c;
		c = rgb_scale(c, att);
	}
	return (c);
}

t_rgb	compute_point_color(t_rt rt, t_primitive p, t_camera c, t_light l, float *z)
{
	t_vec3		position;
	t_vec3		light_dir;
	t_vec3		view_dir;
	t_rgb		color;

	position = (t_vec3){
		(c.ray.origin.x + c.ray.direction.x * *z),
		(c.ray.origin.y + c.ray.direction.y * *z),
		(c.ray.origin.z + c.ray.direction.z * *z)};
	light_dir = compute_lightdir(l, position);
	view_dir = vec3_normalize(vec3_substract(c.ray.origin, position));
	color = compute_illumination(p, l,
		(t_vec3[]){position, light_dir, view_dir, rt.normal[p.type](position, p)});
	return ((t_rgb){clamp(color.r, 0, 1), clamp(color.g, 0, 1), clamp(color.b, 0, 1)});
}

t_vec3				vec3_rotx(const t_vec3 vec, const float r)
{
	float			cos_r;
	float			sin_r;
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

t_vec3				vec3_roty(const t_vec3 vec, const float r)
{
	float			cos_r;
	float			sin_r;
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

t_vec3				vec3_rotz(const t_vec3 vec, const float r)
{
	float			cos_r;
	float			sin_r;
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

t_camera	update_camera(t_camera gopro, float aspect)
{
	t_vec3		v;
	t_vec3		r;
	t_vec3		u;
	float		fov;

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
		v.x, v.y, v.z, 
	}};
	return (gopro);
}

t_ray	generate_ray(t_camera gopro, float x, float y)
{
	t_ray ray;

	ray.origin = gopro.position;
	ray.direction = m3_mult_vec3(gopro.transform,
					new_vec3(x, y, 1));
	return (ray);
}

t_ray	generate_shadow_ray(t_camera c, t_light l, float z)
{
	t_ray	ray;

	ray.origin = (t_vec3){
		(c.ray.origin.x + c.ray.direction.x * z),
		(c.ray.origin.y + c.ray.direction.y * z),
		(c.ray.origin.z + c.ray.direction.z * z)};;
	ray.direction = l.type == DIRECTIONAL ? vec3_normalize(l.position) : vec3_normalize(vec3_substract(l.position, ray.origin));
	//ray.direction = l.type == DIRECTIONAL ? vec3_normalize(l.position) : vec3_normalize(vec3_substract(ray.origin, l.position));
	ray.origin = vec3_add(ray.origin, vec3_scale(ray.direction, 1));
//	if (l.type == SPOT)
//		printf(
//"origin %f, %f, %f\n\
//direction %f, %f, %f\n", ray.origin.x, ray.origin.y, ray.origin.z,  ray.direction.x, ray.direction.y, ray.direction.z);
	return (ray);
}

enum e_bool	in_shadow(t_rt rt, t_light l, double z)
{
	int k;

	k = 0;
	while (k < rt.scene.primitive_nbr)
	{
		t_ray	shadow_ray = generate_shadow_ray(rt.scene.camera, l, z);
		float	fake_z = vec3_distance(l.position, shadow_ray.origin);
		if (rt.intersect[rt.scene.primitive[k].type](rt.scene.primitive[k], shadow_ray, &fake_z))
			return (true);
		k++;
	}
	return (false);
}

float	iterate_through_primitives(t_rt rt, t_point2 obj, t_rgb *color)
{
	float		z;

	z = -1;
	while (obj.x < rt.scene.primitive_nbr)
	{
		if (rt.intersect[rt.scene.primitive[obj.x].type](rt.scene.primitive[obj.x], rt.scene.camera.ray, &z))
		{
			obj.y = 0;
			while (obj.y < rt.scene.light_nbr)
			{
				if (!in_shadow(rt, rt.scene.light[obj.y], z))
					*(color) = obj.y > 0 ? rgb_add(*(color), compute_point_color(rt, rt.scene.primitive[obj.x], rt.scene.camera, rt.scene.light[obj.y], &z)) :
					compute_point_color(rt, rt.scene.primitive[obj.x], rt.scene.camera, rt.scene.light[obj.y], &z);
				else
					*(color) = obj.y > 0 ? rgb_add(*(color), rgba_to_rgb(rt.scene.primitive[obj.x].material.ambient)) : rgba_to_rgb(rt.scene.primitive[obj.x].material.ambient);
				obj.y++;
			}
			z = (z + z) * 0.5;
		}
		obj.x++;
	}
	return (z);
}

t_rgb	iterate_through_pixel(t_point2 size, t_rt rt, t_point2 current)
{
	t_vec2		fcur;
	t_rgb		color[2];
	float		z;
	float		*current_z;
	t_point2	obj;

	fcur.y = current.y;
	color[1] = (t_rgb){0, 0, 0};
	current_z = get_current_z(rt.depth, size, current);
	while (fcur.y < current.y + 1)
	{
		fcur.x = current.x;
		while (fcur.x < current.x + 1)
		{
			obj.x = 0;
			rt.scene.camera.ray = generate_ray(rt.scene.camera, (size.x - 2 * fcur.x), (size.y - 2 * fcur.y));
			color[0] = BACKGROUND;
			z = iterate_through_primitives(rt, obj, &color[0]);
			color[1] = rgb_add(color[1], (t_rgb){color[0].r > 1 ? 1 : color[0].r, color[0].g > 1 ? 1 : color[0].g, color[0].b > 1 ? 1 : color[0].b});
			fcur.x += 1 / ((float)SUPERSAMPLING);
		}
		fcur.y += 1 / ((float)SUPERSAMPLING);
	}
	*(current_z) = z != -1 ? z : *(current_z);
	return (color[1]);
}

void	do_raytracer(t_point2 size, t_rt rt)
{
	t_point2	current;
	t_rgb		final_color;
	

	current.y = 0;
	while (current.y < size.y)
	{
		current.x = 0;
		while (current.x < size.x)
		{
			final_color = iterate_through_pixel(size, rt, current);
			final_color = rgb_divide(final_color, (SUPERSAMPLING) * (SUPERSAMPLING));
			final_color = rgb_scale(final_color, 255);
			put_rgb_to_image(rt.image, current, final_color);
			current.x++;
		}
		current.y++;
	}
}

t_depth_buffer	*new_depth_buffer(t_point2 size)
{
	t_depth_buffer *n;

	n = ft_memalloc(sizeof(t_depth_buffer));
	n->size = size;
	n->buffer = ft_memalloc(sizeof(float*) * size.x);
	while (size.x)
	{
		n->buffer[size.x - 1] = ft_memalloc(sizeof(float) * n->size.y);
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

void	exit_rt(int key, t_rt *rt)
{
	destroy_framework(rt->framework);
	destroy_depth_buffer(rt->depth);
	ft_putstr("kthxbye !\n");
	exit(key);
}

void	move_along_x(int key, t_rt *rt)
{
	rt->scene.camera.position.x += key == LEFTARROW ? 50 : -50;
	rt->scene.camera = update_camera(rt->scene.camera, HEIGHT / (float)WIDTH);
	do_raytracer((t_point2){WIDTH, HEIGHT}, *rt);
	refresh_window(rt->window);
	//printf("%f, %f, %f\n", rt->scene.camera.position.x, rt->scene.camera.position.y, rt->scene.camera.position.z);
}

void	move_along_y(int key, t_rt *rt)
{
	rt->scene.camera.position.y += key == KEYPADPLUS ? 50 : -50;
	rt->scene.camera = update_camera(rt->scene.camera, HEIGHT / (float)WIDTH);
	do_raytracer((t_point2){WIDTH, HEIGHT}, *rt);
	refresh_window(rt->window);
	//printf("%f, %f, %f\n", rt->scene.camera.position.x, rt->scene.camera.position.y, rt->scene.camera.position.z);
}

void	move_along_z(int key, t_rt *rt)
{
	rt->scene.camera.position.z += key == UPARROW ? 50 : -50;
	rt->scene.camera = update_camera(rt->scene.camera, HEIGHT / (float)WIDTH);
	do_raytracer((t_point2){WIDTH, HEIGHT}, *rt);
	refresh_window(rt->window);
	//printf("%f, %f, %f\n", rt->scene.camera.position.x, rt->scene.camera.position.y, rt->scene.camera.position.z);
}

/*
** factors.x == spec_power
** factors.y == roughness
** factors.z == albedo
*/
t_mtl	new_mtl(t_rgba diffuse, t_rgba ambient, t_rgba specular, t_vec3 factors)
{
	t_mtl material;

	material.diffuse = diffuse;
	material.ambient = ambient;
	material.specular = specular;
	material.spec_power = factors.x;
	material.roughness = factors.y;
	material.albedo = factors.z;
	return (material);
}

t_light	new_light(int type, t_vec3 position, t_vec3 direction, t_rgb color, float power, float attenuation, float falloff, float spot_size, float specular)
{
	t_light	l;

	l.type = type;
	l.position = position;
	l.direction = direction;
	l.color = color;
	l.power = power;
	l.attenuation = attenuation;
	l.falloff = falloff;
	l.spot_size = spot_size;
	l.specular = specular;
	return (l);
}

#include <fcntl.h>
# define UINT unsigned int

void save_scene(int keycode, t_scene *scene)
{
	int fd;

	fd = open("scene.rtscene", O_CREAT | O_RDWR, S_IWRITE | S_IREAD);
	write(fd, scene, sizeof(t_scene));
	write(fd, scene->primitive, sizeof(t_primitive) * scene->primitive_nbr);
	write(fd, scene->light, sizeof(t_light) * scene->light_nbr);
	close(fd);
	(void)keycode;
}

void	check_scene_read(UINT readsize, UINT expected)
{
	if (readsize != expected)
	{
		ft_putstr("INVALID MAP !\n");
		exit(-42);
	}
}

t_scene	load_scene(const char *filepath)
{
	t_scene	s;
	char 	dumy[1];
	int		fd;

	fd = open(filepath, O_RDONLY, 0);
	check_scene_read(read(fd, &s, sizeof(t_scene)), sizeof(t_scene));
	check_scene_read(read(fd,
		s.primitive = ft_memalloc(sizeof(t_primitive) * s.primitive_nbr),
		sizeof(t_primitive) * s.primitive_nbr),
		sizeof(t_primitive) * s.primitive_nbr);
	check_scene_read(read(fd,
		s.light = ft_memalloc(sizeof(t_light) * s.light_nbr),
		sizeof(t_light) * s.light_nbr),
		sizeof(t_light) * s.light_nbr);
	check_scene_read(read(fd, dumy, 1), 0);
	close(fd);
	return (s);
}

t_scene	default_scene()
{
	t_scene scene;

	scene.camera = new_camera((t_vec3){50, 0, -550}, (t_vec3){0, -50, 0}, (t_vec3){0, 1, 0}, (t_vec2){TO_RADIAN(30), HEIGHT / (float)WIDTH});
	scene.primitive = ft_memalloc(sizeof(t_primitive) * 2);
	scene.primitive[0] = new_sphere((t_vec3){0, 100, 0}, 100);
	scene.primitive[1] = new_cylinder((t_vec3){0, -100, 0}, (t_vec3){0, 1, 0}, 10, 400);
	scene.primitive[0].material = new_mtl((t_rgba){1, 0, 0, 1}, (t_rgba){0.1, 0, 0, 1}, (t_rgba){1, 1, 1, 1}, (t_vec3){80, 0.2, 1});
	scene.primitive[1].material = new_mtl((t_rgba){1, 1, 1, 1}, (t_rgba){0, 0, 0, 1}, (t_rgba){1, 1, 1, 1}, (t_vec3){10, 1, 1});
	scene.primitive_nbr = 2;
	scene.light = ft_memalloc(sizeof(t_light) * 6);
	scene.light[0] = new_light(POINT, (t_vec3){200, -100, 200}, vec3_negate(vec3_normalize((t_vec3){200, -100, 200})), (t_rgb){1, 1, 0}, 1, 0.002, 200, 80, 1);
	scene.light[1] = new_light(POINT, (t_vec3){-200, -100, 200}, vec3_negate(vec3_normalize((t_vec3){-200, -100, 200})), (t_rgb){1, 0, 1}, 1, 0.002, 200, 80, 1);
	scene.light[2] = new_light(POINT, (t_vec3){-200, -100, -200}, vec3_negate(vec3_normalize((t_vec3){-200, -100, -200})), (t_rgb){0, 1, 1}, 1, 0.002, 200, 80, 1);
	scene.light[3] = new_light(POINT, (t_vec3){200, -100, -200}, vec3_negate(vec3_normalize((t_vec3){200, -100, -200})), (t_rgb){0, 0, 1}, 1, 0.002, 200, 80, 1);
	scene.light[4] = new_light(DIRECTIONAL, (t_vec3){1, 1, 0}, (t_vec3){0, 0, 0}, (t_rgb){1, 1, 1}, 0.5, 0.002, 200, 70, 1);
	scene.light[5] = new_light(DIRECTIONAL, (t_vec3){-1, -1, 0}, (t_vec3){0, 0, 0}, (t_rgb){1, 1, 0.8}, 0.3, 0.002, 200, 70, 0);
	scene.light_nbr = 6;
	ft_putstr("Lollipop ?\n");
	return (scene);
}

int main(int argc, const char** argv)
{
	t_rt	rt;
	if (argc > 1)
		rt.scene = load_scene(argv[1]);
	else
	{
		ft_putstr("Please specify a map !\nCreating default scene...\n");
		rt.scene = default_scene();
	}
	rt.framework = init_framework();
	rt.window = new_window(rt.framework, WIDTH, HEIGHT, "RTv1");
	rt.image = new_image(rt.framework, WIDTH, HEIGHT, "display");
	rt.depth = new_depth_buffer((t_point2){1, 1});
	rt.intersect[SPHERE] = intersect_sphere;
	rt.intersect[CYLINDER] = intersect_cylinder;
	rt.intersect[CONE] = intersect_cone;
	rt.intersect[PLANE] = intersect_plane;
	rt.normal[SPHERE] = sphere_normal;
	rt.normal[CYLINDER] = cylinder_normal;
	rt.normal[CONE] = cone_normal;
	rt.normal[PLANE] = plane_normal;
	attach_image_to_window(rt.image, rt.window);
	fill_image(rt.image, rgb_scale(BACKGROUND, 255));
	refresh_window(rt.window);
	setup_keypress(rt.window, ESCAPE, exit_rt, &rt);
	setup_keypress(rt.window, LEFTARROW, move_along_x, &rt);
	setup_keypress(rt.window, RIGHTARROW, move_along_x, &rt);
	setup_keypress(rt.window, KEYPADPLUS, move_along_y, &rt);
	setup_keypress(rt.window, KEYPADMINUS, move_along_y, &rt);
	setup_keypress(rt.window, UPARROW, move_along_z, &rt);
	setup_keypress(rt.window, DOWNARROW, move_along_z, &rt);
	setup_keypress(rt.window, S_KEY, save_scene, &rt.scene);
	loop_callback(rt.framework, refresh_window, rt.window);
	do_raytracer((t_point2){WIDTH, HEIGHT}, rt);
	init_loop(rt.framework);
	return (0);
}
