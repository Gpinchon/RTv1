# include <rt.h>
#include <stdio.h>


enum e_bool	test_intersect(double t[2], double *current_z)
{
	enum e_bool	retvalue;

	retvalue = false;
	if ((t[0] > DOUBLE_ZERO)
	&& (t[0] < *(current_z) || double_equal(*(current_z), t[0])))
	{
		printf("t0 %f, %f\n", *(current_z), t[0]);
		*(current_z) = t[0];
		retvalue = true;
		printf("%f\n", *(current_z));
	}
	if (!double_equal(t[0], t[1])
	&& (t[1] > DOUBLE_ZERO) 
	&& (t[1] < *(current_z) || double_equal(*(current_z), t[1])))
	{
		printf("t1 %f, %f\n", *(current_z), t[1]);
		*(current_z) = t[1];
		retvalue = true;
		printf("%f\n", *(current_z));
	}
	return (retvalue);
}

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
//	if (delta <= 0)
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
//	t_vec3 rdd = vec3_substract(r.direction, vec3_scale(cp.direction, vec3_dot(r.direction, cp.direction)));
//	t_vec3 od = vec3_substract(o, vec3_scale(cp.direction, vec3_dot(o, cp.direction)));
//
//	double a = vec3_dot(rdd, rdd);
//	double b = 2 * vec3_dot(rdd, od);
//	double c = vec3_dot(od, od) - cp.radius * cp.radius;
//	double	t[2];
//	double delta;
//	delta = sqrt((b * b) - (4.0 * a * c));
//	if (delta <= 0)
//		return (false);
//	t[0] = (-b - (delta)) / (2.0 * a);
//	t[1] = (-b + (delta)) / (2.0 * a);
//	return (test_intersect(t, current_z));
//}

enum e_bool	intersect_inf_cylinder(t_primitive cp, t_ray r, double *current_z)
{
	t_vec3	pdp = vec3_substract(cp.direction, cp.position);
	t_vec3	eyexpdp = vec3_cross(vec3_substract(r.origin, cp.position), pdp);
	t_vec3	rdxpdp = vec3_cross(r.direction, pdp);
	double	a = vec3_dot(rdxpdp, rdxpdp);
	double	b = 2 * vec3_dot(rdxpdp, eyexpdp);
	double	c = vec3_dot(eyexpdp, eyexpdp) - (cp.radius * cp.radius * vec3_dot(pdp, pdp));
	double	t[2];
	double delta;
	delta = sqrt((b * b) - (4.0 * a * c));
	if (delta <= 0)
		return (false);
	t[0] = (-b - (delta)) / (2.0 * a);
	t[1] = (-b + (delta)) / (2.0 * a);
	return (test_intersect(t, current_z));
}
//D = raydir
//O = rayorigin
//X = eye
//t_vec3 eye = vec3_substract(r.origin, cp.position);
//double hangle = 1 + cp.radius * cp.radius;
//double a   = vec3_dot(r.direction, r.direction) - hangle * pow(vec3_dot(r.direction, cp.direction), 2);
//double b   = 2 * (vec3_dot(r.direction, X) - hangle * vec3_dot(r.direction, cp.direction) * vec3_dot(X, cp.direction));
//double c   = vec3_dot(X, X) - hangle * pow(vec3_dot(X, cp.direction), 2);

enum e_bool	intersect_inf_cone(t_primitive cp, t_ray r, double *current_z)
{
	double alpha = TO_RADIAN(cp.radius);
	t_vec3 eye = vec3_substract(r.origin, cp.position);
	t_vec3 tmp1 = vec3_substract(r.direction, vec3_scale(cp.direction, vec3_dot(r.direction, cp.direction)));
	t_vec3 tmp2 = vec3_substract(eye, vec3_scale(cp.direction, vec3_dot(eye, cp.direction)));
	double a = pow(cos(alpha), 2) * vec3_dot(tmp1, tmp1) - pow(sin(alpha), 2) * pow(vec3_dot(r.direction, cp.direction), 2);
	double b = 2 * (pow(cos(alpha), 2) * vec3_dot(tmp1, tmp2)) - 2 * (pow(sin(alpha), 2) * vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction));
	double c = pow(cos(alpha), 2) * vec3_dot(tmp2, tmp2) - pow(sin(alpha), 2) * pow(vec3_dot(eye, cp.direction), 2);
	//t_vec3 eye = vec3_substract(r.origin, cp.position);
	//double hangle = 1 + TO_RADIAN(cp.radius) * TO_RADIAN(cp.radius);
	//double a   = vec3_dot(r.direction, r.direction) - hangle * pow(vec3_dot(r.direction, cp.direction), 2);
	//double b   = 2 * (vec3_dot(r.direction, eye) - hangle * vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction));
	//double c   = vec3_dot(eye, eye) - hangle * pow(vec3_dot(eye, cp.direction), 2);
	//t_vec3 eye = vec3_substract(r.origin, cp.position);
	//double radius = TO_RADIAN(cp.radius);
	//double a = (cp.position.x * cp.position.x) + (cp.position.y * cp.position.y) - ((cp.position.z * cp.position.z) * radius);
	//double b = 2.0 * (eye.x * cp.position.x + eye.y * cp.position.y - eye.z * cp.position.z * radius);
	//double c = (eye.x * eye.x) + (eye.y * eye.y) - ((eye.z * eye.z) * radius);
	//t_vec3 va = (t_vec3){0, -1, 0};
	//double cos2a = cos(cp.radius);
	//double sin2a = 1 - cos2a;
	//t_vec3 eye = vec3_substract(r.origin, cp.position);
	//double c1 = vec3_dot(r.direction, va);
	//t_vec3 c2 = vec3_cross(va, r.direction);
	//double c3 = vec3_dot(eye, va);
	//t_vec3 c4 = vec3_scale(va, c3);
//
	//double a = cos2a * vec3_length(vec3_substract(r.direction, c2)) - sin2a * c1 * c1;
	//double b = 2.0 * cos2a * vec3_dot(vec3_substract(r.direction, c2), vec3_substract(eye, c4)) - 2.0 * sin2a * (c1 * c3);
	//double c = cos2a * vec3_length(vec3_substract(eye, c4)) - sin2a * (c3 * c3);
//
	//t_vec3 eye = vec3_substract(r.origin, cp.position);
	//double tmp = (1 + TO_RADIAN(cp.radius) * TO_RADIAN(cp.radius));
	//double a = vec3_dot(r.direction, r.direction);
	//a = a - (tmp * pow(vec3_dot(r.direction, cp.direction), 2));
	//double b = vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction);
	//b = 2 * (vec3_dot(r.direction, eye) - b * tmp);
	//double c = vec3_dot(eye, eye);
	//c -= tmp * pow(vec3_dot(eye, cp.direction), 2);
	double	t[2];
	double	delta;
	delta = sqrt((b * b) - (4.0 * a * c));
	if (delta <= 0)
		return (false);
	t[0] = (-b - delta) / (2.0 * a);
	t[1] = (-b + delta) / (2.0 * a);
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
		eye = vec3_substract(vec3_add(r.origin, vec3_scale(r.direction, *current_z)), cp.position);
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
	if (t <= 0)
		return (false);
	*current_z = t;
	return (true);
}