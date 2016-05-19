# include <rt.h>

enum e_bool	test_intersect(double t[2], double *current_z)
{
	enum e_bool	retvalue;

	retvalue = false;
	if ((t[0] > DOUBLE_ZERO)
	&& (t[0] < *(current_z) || double_equal(*(current_z), t[0])))
	{
		*(current_z) = t[0];
		retvalue = true;
	}
	if (!double_equal(t[0], t[1])
	&& (t[1] > DOUBLE_ZERO) 
	&& (t[1] < *(current_z) || double_equal(*(current_z), t[1])))
	{
		*(current_z) = t[1];
		retvalue = true;
	}
	return (retvalue);
}

enum e_bool	intersect_sphere(t_primitive s, t_ray r, double *current_z)
{
	t_vec3	dist = vec3_substract(s.position, r.origin);
	double	B = vec3_dot(r.direction, dist);
	double	D = B * B - vec3_dot(dist, dist) + s.radius * s.radius;
	double	t[2];
	if (D < DOUBLE_ZERO)
		return (false);
	t[0] = B - sqrt(D);
	t[1] = B + sqrt(D);
	return (test_intersect(t, current_z));
}

#include <stdio.h>

void	swap(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

enum e_bool Quadratic(double A, double B, double C, double *t0, double *t1)
{
	double discrim = B * B - 4.f * A * C;
	if (discrim <= DOUBLE_ZERO)
		return false;
	double rootDiscrim = sqrtf(discrim);
	double q;
	if (B < 0)
		q = -.5f * (B - rootDiscrim);
	else
		q = -.5f * (B + rootDiscrim);
	*t0 = q / A;
	*t1 = C / q;
	if (*t0 > *t1)
		swap(t0, t1);
	return true;
}

enum e_bool	intersect_cylinder(t_primitive cp, t_ray r, double *current_z)
{
	t_vec3 eye = vec3_substract(cp.position, r.origin);
	double a = r.direction.x * r.direction.x + r.direction.y * r.direction.y;
	double b = 2.0 * (eye.x * r.direction.x + eye.y * r.direction.y);
	double c = eye.x * eye.x + eye.y * eye.y - cp.radius * cp.radius;
	//double a = vec3_dot(r.direction, r.direction);
	//double b = 2.f * (vec3_dot(eye, r.direction));
	//double c = vec3_dot(eye, eye) - cp.radius * cp.radius;
	double	t[2];
	t[0] = (-b - sqrt((b * b) - (4.0 * a * c))) / (2.0 * a);
	t[1] = (-b + sqrt((b * b) - (4.0 * a * c))) / (2.0 * a);
	//if (!Quadratic(a, b, c, &t[0], &t[1]))
	//	return (false);
	return (test_intersect(t, current_z));
}