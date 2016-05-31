# include <libft.h>
# include <mlx_framework.h>
# include <adv_math.h>

# define	WIDTH			1024
# define	HEIGHT			768
# define	DIFFUSE			oren_nayar_diffuse
# define	SPECULAR		trowbridge_reitz_specular
# define	DIRECTIONAL		0
# define	SPOT			1
# define	POINT			2

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

typedef struct	s_generic_prim
{
	int			type;
}				t_generic_prim;

typedef	struct	s_primitive
{
	int			type;
	t_mtl		material;
	t_vec3		position;
	t_vec3		direction;
	double		radius;
	double		size;
}				t_primitive;

typedef struct	s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}				t_ray;

typedef struct	s_camera
{
	t_vec3	position;
	t_vec3	direction;
	t_ray	ray;
	float	fov;
}				t_camera;

typedef struct	s_light
{
	float	power;
	float	attenuation;
	float	falloff;
	float	spot_size;
	int		type;
	t_rgb	color;
	t_vec3	position;
	t_vec3	direction;
}				t_light;

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
** Light comutation functions
*/
float	trowbridge_reitz_specular(t_vec3 normal, t_vec3 view, t_vec3 light, float spec_power);
float	blinn_phong_specular(t_vec3 normal, t_vec3 view, t_vec3 light, float spec_power);
float	oren_nayar_diffuse(t_vec3 normal, t_vec3 view, t_vec3 light, t_mtl mtl);
float	lambert_diffuse(t_vec3 normal, t_vec3 view, t_vec3 light, t_mtl mtl);
t_vec3	compute_lightdir(t_light l, t_vec3 position);
/*
** Primitive intersection funcitons
*/
enum e_bool	intersect_sphere(t_primitive s, t_ray r, double *current_z);
enum e_bool	intersect_cylinder(t_primitive s, t_ray r, double *current_z);
enum e_bool	intersect_cone(t_primitive cp, t_ray r, double *current_z);
enum e_bool	intersect_plane(t_primitive cp, t_ray ray, double *current_z);
