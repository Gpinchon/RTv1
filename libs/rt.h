/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 00:07:03 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/23 18:23:15 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <libft.h>
# include <sdl_framework.h>
# include <adv_math.h>
# include <keys.h>
# include <fcntl.h>

# define SUPERSAMPLING	1
# define WIDTH			512
# define HEIGHT			512
# define BACKGROUND	(t_rgb){0.5, 0.5, 0.5}
# define DIFFUSE		oren_nayar_diffuse
# define SPECULAR	trowbridge_reitz_specular
# define DIRECTIONAL	0x0
# define SPOT		0x1
# define POINT		0x2
# define MAX_OBJ	10000

/*
** Primitives types
*/

# define SPHERE		0x0
# define CYLINDER	0x1
# define CONE		0x3
# define PLANE		0x4
# define MAX_PRIM	0x5

typedef struct	s_mtl
{
	t_rgba		diffuse;
	t_rgba		ambient;
	t_rgba		specular;
	float		spec_power;
	float		roughness;
	float		albedo;
	float		refl;
}				t_mtl;

typedef	struct	s_primitive
{
	UCHAR		type;
	int			mtl_index;
	t_mtl		material;
	t_vec3		position;
	t_vec3		direction;
	float		radius;
	float		radius2;
	float		size;
}				t_primitive;

typedef struct	s_light
{
	UCHAR	type;
	float	power;
	float	attenuation;
	float	falloff;
	float	spot_size;
	float	specular;
	t_rgb	color;
	t_vec3	position;
	t_vec3	direction;
}				t_light;

typedef struct	s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}				t_ray;

typedef struct	s_camera
{
	float	fov;
	t_vec3	up;
	t_vec3	position;
	t_vec3	lookat;
	t_ray	ray;
	t_mat3	transform;
}				t_camera;

typedef struct	s_scene
{
	t_camera	camera;
	int			primitive_nbr;
	int			light_nbr;
	t_primitive	*primitive;
	t_light		*light;
}				t_scene;

typedef struct	s_zbuffer
{
	float		**buffer;
	t_point2	size;
}				t_zbuffer;

typedef struct	s_rt
{
	void		*framework;
	void		*window;
	void		*image;
	enum e_bool	(*intersect[MAX_PRIM])();
	t_vec3		(*normal[MAX_PRIM])();
	t_scene		scene;
	t_zbuffer	*depth;
}				t_rt;

/*
** New mtlight
*/
t_mtl			new_mtl(t_rgba dif, t_rgba amb, t_rgba spec, t_vec3 factors);
t_light			new_light(int type, t_vec3 pdc[3], float factors[6]);
/*
** Material Creation
** factors.x == spec_power
** factors.y == roughness
** factors.z == albedo
*/
t_mtl			new_mtl(t_rgba diffuse, t_rgba ambient,
	t_rgba specular, t_vec3 factors);
/*
** Light Creation
*/
t_light			new_light(int type, t_vec3 pdc[3], float factors[6]);
/*
** Raytracer functions
*/
t_rgb			iterate_through_pixel(t_point2 size, t_rt rt, t_point2 current);
void			do_raytracer(t_point2 size, t_rt rt);
t_rgb			point_color(t_rt rt, t_primitive p, t_light l, float *z);
t_ray			generate_shadow_ray(t_camera c, t_light l, float z);
/*
** Scene functions
*/
void			save_scene(int keycode, t_scene *scene);
void			check_scene_read(UINT readsize, UINT expected);
t_scene			load_scene(const char *filepath);
void			default_lights(t_scene *s);
t_scene			default_scene();
/*
** Z buffer functions
*/
t_zbuffer		*new_depth_buffer(t_point2 size);
void			*destroy_depth_buffer(t_zbuffer *d);
float			*get_current_z(t_zbuffer *depth,
	t_point2 screen_size, t_point2 current);
/*
** Keys functions
*/
void			exit_rt(int key, t_rt *rt);
void			move_along_x(int key, t_rt *rt);
void			move_along_y(int key, t_rt *rt);
void			move_along_z(int key, t_rt *rt);
/*
** Camera functions
*/
t_camera		new_camera(t_vec3 position, t_vec3 lookat, t_vec3 up, t_vec2 d);
t_camera		update_camera(t_camera gopro, float aspect);
t_ray			generate_ray(t_camera gopro, float x, float y);
/*
** Light computation functions
*/
float			trowbridge_reitz_specular(t_vec3 normal, t_vec3 view,
	t_vec3 light, float spec_power);
float			blinn_phong_specular(t_vec3 normal, t_vec3 view, t_vec3 light,
	float spec_power);
float			oren_nayar_diffuse(t_vec3 normal, t_vec3 view, t_vec3 light,
	t_mtl mtl);
float			lambert_diffuse(t_vec3 normal, t_vec3 view, t_vec3 light,
	t_mtl mtl);
t_vec3			compute_lightdir(t_light l, t_vec3 position);
/*
** Primitive intersection functions
*/
enum e_bool		intersect_sphere(t_primitive s, t_ray r, float *current_z);
enum e_bool		intersect_cylinder(t_primitive cp, t_ray r, float *current_z);
enum e_bool		intersect_cone(t_primitive cp, t_ray r, float *current_z);
enum e_bool		intersect_plane(t_primitive cp, t_ray ray, float *current_z);
enum e_bool		test_intersect(float t[2], float *current_z);
enum e_bool		solve_quadratic(float a, float b, float c, float *t);
void			float_swap(float *a, float *b);
/*
** Primitive creation functions
*/
t_primitive		new_sphere(t_vec3 position, float radius);
t_primitive		new_cylinder(t_vec3 position, t_vec3 direction,
	float radius, float size);
t_primitive		new_cone(t_vec3 position, t_vec3 direction,
	float radius, float size);
t_primitive		new_plane(t_vec3 position, t_vec3 direction);
/*
** Primitive normal computation functions
*/
t_vec3			cylinder_normal(t_vec3 position, t_primitive p);
t_vec3			sphere_normal(t_vec3 position, t_primitive p);
t_vec3			plane_normal(t_vec3 position, t_primitive p);
t_vec3			cone_normal(t_vec3 position, t_primitive p);
#endif
