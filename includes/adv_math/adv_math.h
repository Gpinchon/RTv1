#ifndef ADV_MATH_H
# define ADV_MATH_H
# define FLOAT_ZERO		0.0001f
# define DOUBLE_ZERO	0.000001
# define TO_DEGREE(x)	((int)(180 * x / M_PI) % 360)
# define TO_RADIAN(x)	(x / 180.0f * M_PI)
# include <math.h>

enum			e_bool
{
	false = 0x0, true = !false
};

typedef	struct		s_mat4
{
	float			m[16];
}					t_mat4;

typedef struct	s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_vec4
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vec4;

/*
** Vector math
*/
double	vec3_dot(t_vec3 v1, t_vec3 v2);
double	vec3_distance(t_vec3 v, t_vec3 v1);
t_vec3	vec3_add(t_vec3 vector1, t_vec3 vector2);
t_vec3	vec3_substract(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_multiply(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_cross(t_vec3 vector1, t_vec3 vector2);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_scale(t_vec3 v, double d);
t_vec3	vec3_divide(t_vec3, double d);
t_vec3	vec3_abs(t_vec3 v);
t_vec3	vec3_negate(t_vec3 v);
/*
** Scalar math
*/
double	vec3_length(t_vec3 v);
/*
** Linear interpolation
*/
float	float_lerp(float start, float end, float percent);
/*
** Quadratic interpolation
*/
float	float_qlerp(float start, float end, float amount);
/*
** OpenGL-like step
*/
float	float_step(float a, float x);
enum e_bool	double_equal(double a, double b);
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

#endif