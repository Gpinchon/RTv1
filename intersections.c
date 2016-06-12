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

#include <stdio.h>


enum e_bool	intersect_sphere(t_primitive s, t_ray r, double *current_z)
{
	t_vec3 eye = vec3_substract(r.origin, s.position);
	double a = vec3_dot(r.direction, r.direction);
	double b = vec3_dot(eye, r.direction) * 2.0;
	double c = vec3_dot(eye, eye) - (s.radius * s.radius);
	double	t[2];
	double delta;
	delta = sqrt((b * b) - (4.0 * a * c));
	if (delta <= 0)
		return (false);
	t[0] = (-b - delta) / (2.0 * a);
	t[1] = (-b + delta) / (2.0 * a);
	return (test_intersect(t, current_z));
}

void	double_swap(double *a, double *b)
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
		double_swap(t0, t1);
	return true;
}

//enum e_bool	intersect_cylinder(t_primitive cp, t_ray r, double *current_z)
//{
//	double	a = (r.direction.x * r.direction.x) + (r.direction.y * r.direction.y);
//	double	b = 2.0 * ((r.origin.x * r.direction.x) + (r.origin.y * r.direction.y));
//	double	c = (r.origin.x * r.origin.x) + (r.origin.y * r.origin.y)
//		- (cp.radius * cp.radius);
//	double	t[2];
//	double delta;
//	delta = sqrt((b * b) - (4.0 * a * c));
//	if (delta < 0)
//		return (false);
//	t[0] = (-b - delta) / (2.0 * a);
//	t[1] = (-b + delta) / (2.0 * a);
//	return (test_intersect(t, current_z));
//}

//enum e_bool	intersect_cylinder(t_primitive cp, t_ray r, double *current_z)
//{
//	t_vec3 eye = vec3_substract(r.origin, cp.position);
//	double	a = (r.direction.x * r.direction.x) + (r.direction.z * r.direction.z);
//	double	b = 2.0 * ((eye.x * r.direction.x) + (eye.z * r.direction.z));
//	double	c = (eye.x * eye.x) + (eye.z * eye.z)
//		- (cp.radius * cp.radius);
//	double	t[2];
//	double delta;
//	delta = sqrt((b * b) - (4.0 * a * c));
//	if (delta <= 0)
//		return (false);
//	t[0] = (-b - delta) / (2.0 * a);
//	t[1] = (-b + delta) / (2.0 * a);
//	return (test_intersect(t, current_z));
//}

//enum e_bool	intersect_cylinder(t_primitive cp, t_ray r, double *current_z)
//{
//	t_vec3 eye = vec3_substract(r.origin, cp.position);
//	double 	a = vec3_dot(r.direction, r.direction) - pow(vec3_dot(r.direction, cp.direction), 2);
//	double 	b = (vec3_dot(r.direction, eye) - vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction)) * 2.0;
//	double 	c = vec3_dot(eye, eye) - pow(vec3_dot(eye, cp.direction), 2) - (cp.radius * cp.radius);
//	double	t[2];
//	double delta;
//	delta = sqrt((b * b) - (4.0 * a * c));
//	if (delta <= 0)
//		return (false);
//	t[0] = (-b - delta) / (2.0 * a);
//	t[1] = (-b + delta) / (2.0 * a);
//	return (test_intersect(t, current_z));
//}

//enum e_bool	intersect_cylinder(t_primitive cp, t_ray r, double *current_z)
//{
//	t_vec3 o = vec3_substract(r.origin, cp.position);
//	t_vec3 rdd = vec3_substract(r.direction, vec3_fscale(cp.direction, vec3_dot(r.direction, cp.direction)));
//	t_vec3 od = vec3_substract(o, vec3_fscale(cp.direction, vec3_dot(o, cp.direction)));
//
//	double a = vec3_dot(rdd, rdd);
//	double b = 2 * vec3_dot(rdd, od);
//	double c = vec3_dot(od, od) - cp.radius * cp.radius;
//	double	t[2];
//	double delta;
//	delta = sqrt((b * b) - (4.0 * a * c));
//	if (delta < 0)
//		return (false);
//	t[0] = (-b - (delta)) / (2.0 * a);
//	t[1] = (-b + (delta)) / (2.0 * a);
//	return (test_intersect(t, current_z));
//}

//a   = r.direction|r.direction - (r.direction|cp.direction)^2
//b =  2 * (r.direction|eye - (r.direction|cp.direction)*(eye|cp.direction))
//c   = eye|eye - (eye|cp.direction)^2 - cp.radius*cp.radius

enum e_bool	intersect_cylinder(t_primitive cp, t_ray r, double *current_z)
{
	t_vec3 eye = vec3_substract(r.origin, cp.position);
	double a = vec3_dot(r.direction, r.direction) - pow(vec3_dot(r.direction, cp.direction), 2);
	double b = 2 * (vec3_dot(r.direction, eye) - vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction));
	double c = vec3_dot(eye, eye) - pow(vec3_dot(eye, cp.direction), 2) - cp.radius * cp.radius;
	double	t[2];
	double delta;
	delta = sqrt((b * b) - (4.0 * a * c));
	if (delta < 0)
		return (false);
	t[0] = (-b - (delta)) / (2.0 * a);
	t[1] = (-b + (delta)) / (2.0 * a);
	return (test_intersect(t, current_z));
}


enum e_bool	intersect_cone(t_primitive cp, t_ray r, double *current_z)
{
	double	a;
	double	b;
	double	c;
	double	tmp;
	t_vec3	eye;

	eye = vec3_substract(r.origin, cp.position);
	tmp = (1 + cp.radius * cp.radius);
	a = vec3_dot(r.direction, r.direction);
	a = a - (tmp * pow(vec3_dot(r.direction, cp.direction), 2));
	b = vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction);
	b = 2 * (vec3_dot(r.direction, eye) - b * tmp);
	c = vec3_dot(eye, eye);
	c -= tmp * pow(vec3_dot(eye, cp.direction), 2);
	double	t[2];
	double	delta;
	delta = sqrt((b * b) - (4.0 * a * c));
	if (delta <= 0)
		return (false);
	t[0] = (-b - delta) / (2.0 * a);
	t[1] = (-b + delta) / (2.0 * a);
	if (test_intersect(t, current_z))
	{
		eye = vec3_substract(vec3_add(r.origin, vec3_fscale(r.direction, *current_z)), cp.position);
		if (cp.size == 0 || cp.direction.x > 0)
			return (true);
		else if (cp.size > 0. && vec3_dot(cp.direction, eye) > 0.)
			if ((cp.size / cos(atan(cp.radius)) > vec3_length(eye)))
				return (true);
	}
	return (false);
}

enum e_bool	intersect_plane(t_primitive cp, t_ray r, double *current_z)
{
	double	m;
	double	t;
	double	d;
	t_vec3	eye;

	eye = vec3_substract(r.origin, cp.position);
	m = vec3_dot(cp.direction, eye);
	if (m < 0)
		return (false);
	d = vec3_dot(cp.direction, r.direction);
	t = -m / d;
	if (t < 0)
		return (false);
	*current_z = t;
	return (true);
}