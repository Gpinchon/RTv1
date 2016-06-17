#ifndef ADV_MATH_H
# define ADV_MATH_H
# define FLOAT_ZERO		0.0001f
# define DOUBLE_ZERO	0.000001
# define TO_DEGREE(x)	((int)(180.0f * x / M_PI) % 360)
# define TO_RADIAN(x)	(x / 180.0f * M_PI)
# include <math.h>

# pragma pack (1)

enum			e_bool
{
	false = 0x0, true = !false
};

typedef	struct		s_mat3
{
	float			m[9];
}					t_mat3;

typedef	struct		s_mat4
{
	float			m[16];
}					t_mat4;

typedef struct	s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

# pragma pack ()

/*
** Vector creation
*/
t_vec3	new_vec3(float x, float y, float z);
t_vec3	vec2_to_vec3(t_vec2 v);
t_vec3	vec4_to_vec3(t_vec4 v);
/*
** Vector math
*/
float	vec3_dot(t_vec3 v, t_vec3 v1);
float	vec3_distance(t_vec3 v, t_vec3 v1);
t_vec3	vec3_add(t_vec3 v, t_vec3 v1);
t_vec3	vec3_substract(t_vec3 v, t_vec3 v1);
t_vec3	vec3_multiply(t_vec3 v, t_vec3 v1);
t_vec3	vec3_cross(t_vec3 v, t_vec3 v1);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_divide(t_vec3, t_vec3 v1);
t_vec3	vec3_scale(t_vec3 v, float d);
t_vec3	vec3_fdivide(t_vec3 v, float d);
t_vec3	vec3_abs(t_vec3 v);
t_vec3	vec3_negate(t_vec3 v);
t_vec3	vec3_project(t_vec3 v, t_vec3 v1);
float	vec3_length(t_vec3 v);
/*
** Linear Interpolation
*/
t_vec3	vec3_lerp(t_vec3 start, t_vec3 end, float percent);
/*
** Smooth Interpolation
*/
t_vec3	vec3_smoothlerp(t_vec3 start, t_vec3 end, float percent);
/*
** Spherical Interpolation
*/
t_vec3	vec3_slerp(t_vec3 start, t_vec3 end, float percent);
/*
** Normalized Interpolation
*/
t_vec3	vec3_nlerp(t_vec3 start, t_vec3 end, float percent);

/*
** Scalar math
** Linear interpolation
*/
float	float_lerp(float start, float end, float percent);
/*
** Smooth interpolation
*/
float	float_smoothlerp(float start, float end, float amount);
/*
** OpenGL-like step
*/
float	float_step(float a, float x);
enum e_bool	double_equal(double a, double b);
enum e_bool	float_equal(float a, float b);
/*
** Matrix functions
*/
t_mat4	m4_identity(void);
t_mat4	m4_zero(void);
t_mat4	m4_lookat(t_vec3 eye, t_vec3 target, t_vec3 up);
t_mat4	m4_persp(float fov, float aspect, float znear, float zfar);
t_mat4	m4_ortho(t_vec4 frustum, float znear, float zfar);
t_vec3	m4_mult_vec3(t_mat4 m, t_vec3 v);
t_vec4	m4_mult_vec4(t_mat4 m, t_vec4 v);
t_mat4	m4_invert(const t_mat4 i);
t_mat4	m4_transpose(t_mat4 in);
/*
** Matrix 3 functions
*/
t_mat3	m3_identity(void);
t_mat3	m3_zero(void);
t_vec3	m3_mult_vec3(t_mat3 m, t_vec3 v);

#endif