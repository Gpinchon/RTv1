# include <libft.h>
# include <mlx_framework.h>
# include <adv_math.h>

# define	WIDTH			1920
# define	HEIGHT			1080
# define	DIFFUSE			oren_nayar_diffuse
# define	SPECULAR		trowbridge_reitz_specular
# define	DIRECTIONAL		0x0
# define	SPOT			0x1
# define	POINT			0x2
/*
** Structure types
*/
# define	PRIMITIVE		0
# define	LIGHT			1

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

typedef struct	s_gen_struct
{
	UCHAR		struct_type;
	struct s_gen_struct	*next;
	struct s_gen_struct	*prev;
}				t_gen_struct;

typedef	struct	s_primitive
{
	UCHAR		struct_type;
	struct s_primitive	*next;
	struct s_primitive	*prev;
	UCHAR		type;
	t_mtl		material;
	t_vec3		position;
	t_vec3		direction;
	float		radius;
	float		size;
}				t_primitive;

typedef struct	s_light
{
	UCHAR	struct_type;
	struct s_light	*next;
	struct s_light	*prev;
	UCHAR	type;
	float	power;
	float	attenuation;
	float	falloff;
	float	spot_size;
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
	t_vec3	direction;
	t_ray	ray;
	t_mat3	transform;
}				t_camera;

typedef struct	s_scene
{
	t_camera	camera;
	t_light		*lights;
	t_primitive	*primitives;
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
** Primitive intersection funcitons
*/
enum e_bool	intersect_sphere(t_primitive s, t_ray r, double *current_z);
enum e_bool	intersect_inf_cylinder(t_primitive s, t_ray r, double *current_z);
enum e_bool	intersect_inf_cone(t_primitive cp, t_ray r, double *current_z);
enum e_bool	intersect_plane(t_primitive cp, t_ray ray, double *current_z);