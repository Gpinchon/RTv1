# include <libft.h>
# include <mlx_framework.h>
# include <adv_math.h>

# define	WIDTH		512
# define	HEIGHT		512
# define	DIFFUSE		oren_nayar_diffuse
# define	SPECULAR	trowbridge_reitz_specular
# define	DIRECTIONAL	0x0
# define	SPOT		0x1
# define	POINT		0x2
/*
** Primitives types
*/
# define	SPHERE		0x0
# define	CYLINDER	0x1
# define	CONE		0x3
# define	PLANE		0x4

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
	float		size;
	enum e_bool	(*intersect)();
	t_vec3		(*normal)();
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
	t_light		*light;
	t_primitive	*primitive;
	t_mtl		*materials;
}				t_scene;

typedef struct	s_depth_buffer
{
	double		**buffer;
	t_point2	size;
}				t_depth_buffer;

typedef struct	s_rt
{
	void			*framework;
	void			*window;
	void			*image;
	t_depth_buffer	*depth;
}				t_rt;

/*
** Light computation functions
*/
float	trowbridge_reitz_specular(t_vec3 normal, t_vec3 view, t_vec3 light, float spec_power);
float	blinn_phong_specular(t_vec3 normal, t_vec3 view, t_vec3 light, float spec_power);
float	oren_nayar_diffuse(t_vec3 normal, t_vec3 view, t_vec3 light, t_mtl mtl);
float	lambert_diffuse(t_vec3 normal, t_vec3 view, t_vec3 light, t_mtl mtl);
t_vec3	compute_lightdir(t_light l, t_vec3 position);
/*
** Primitive intersection functions
*/
enum e_bool	intersect_sphere(t_primitive s, t_ray r, double *current_z);
enum e_bool	intersect_cylinder(t_primitive cp, t_ray r, double *current_z);
enum e_bool	intersect_cone(t_primitive cp, t_ray r, double *current_z);
enum e_bool	intersect_plane(t_primitive cp, t_ray ray, double *current_z);
/*
** Primitive creation functions
*/
t_primitive	new_sphere(t_vec3 position, double radius);
t_primitive	new_cylinder(t_vec3 position, t_vec3 direction, double radius, double size);
t_primitive	new_cone(t_vec3 position, t_vec3 direction, double radius, double size);
t_primitive	new_plane(t_vec3 position, t_vec3 direction);
/*
** Primitive normal computation functions
*/
t_vec3	cylinder_normal(t_vec3 position, t_primitive p);
t_vec3	sphere_normal(t_vec3 position, t_primitive p);
t_vec3	plane_normal(t_vec3 position, t_primitive p);
t_vec3	cone_normal(t_vec3 position, t_primitive p);