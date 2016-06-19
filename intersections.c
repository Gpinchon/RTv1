# include <rt.h>
#include <stdio.h>


enum e_bool	test_intersect(float t[2], float *current_z)
{
	enum e_bool	retvalue;

	retvalue = false;
	//printf("%f, %f\n", t[0], t[1]);
	if ((t[0] > DOUBLE_ZERO)
	&& (t[0] < *(current_z) || *current_z == -1 || float_equal(*(current_z), t[0])))
	{
		*(current_z) = t[0];
		retvalue = true;
	}
	if (!float_equal(t[0], t[1])
	&& (t[1] > DOUBLE_ZERO) 
	&& (t[1] < *(current_z) || *current_z == -1 || float_equal(*(current_z), t[1])))
	{
		*(current_z) = t[1];
		retvalue = true;
	}
	return (retvalue);
}

enum e_bool	intersect_sphere(t_primitive s, t_ray r, float *current_z)
{
	t_vec3 eye = vec3_substract(r.origin, s.position);
	float a = vec3_dot(r.direction, r.direction);
	float b = vec3_dot(eye, r.direction) * 2.0;
	float c = vec3_dot(eye, eye) - (s.radius * s.radius);
	float	t[2];
	float delta;
	delta = sqrt((b * b) - (4.0 * a * c));
	if (delta <= 0)
		return (false);
	t[0] = (-b - delta) / (2.0 * a);
	t[1] = (-b + delta) / (2.0 * a);
	return (test_intersect(t, current_z));
}

void	float_swap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

enum e_bool Quadratic(float A, float B, float C, float *t0, float *t1)
{
	float discrim = B * B - 4.f * A * C;
	if (discrim <= DOUBLE_ZERO)
		return false;
	float rootDiscrim = sqrtf(discrim);
	float q;
	if (B < 0)
		q = -.5f * (B - rootDiscrim);
	else
		q = -.5f * (B + rootDiscrim);
	*t0 = q / A;
	*t1 = C / q;
	if (*t0 > *t1)
		float_swap(t0, t1);
	return true;
}

//c.position = cylinder center
//c.direction = cylinder axis (unit vector)
//r.origin = ray origin
//r.direction = ray direction (unit vector)


enum e_bool	intersect_inf_cylinder(t_primitive cp, t_ray r, float *current_z)
{
	t_vec3 Cperp = vec3_substract(cp.position, vec3_project(cp.position, cp.direction));
	t_vec3 Pperp = vec3_substract(r.origin, vec3_project(r.origin, cp.direction));
	t_vec3 Dperp = vec3_substract(r.direction, vec3_project(r.direction, cp.direction));
	t_vec3 eye = vec3_substract(Pperp, Cperp);
	float a = vec3_dot(Dperp, Dperp);
	float b = vec3_dot(eye, Dperp) * 2.0;
	float c = vec3_dot(eye, eye) - (cp.radius * cp.radius);
	float	t[2];
	float delta;
	delta = sqrt((b * b) - (4.0 * a * c));
	if (delta <= 0)
		return (false);
	t[0] = (-b - delta) / (2.0 * a);
	t[1] = (-b + delta) / (2.0 * a);
	return (test_intersect(t, current_z));
}

enum e_bool	intersect_cylinder(t_primitive cp, t_ray r, float *current_z)
{
	t_vec3 Cpar = vec3_project(cp.position, cp.direction);
	t_vec3 Cperp = vec3_substract(cp.position, Cpar);
	t_vec3 Ppar = vec3_project(r.origin, cp.direction);
	t_vec3 Pperp = vec3_substract(r.origin, Ppar);
	t_vec3 Dpar = vec3_project(r.direction, cp.direction);
	t_vec3 Dperp = vec3_substract(r.direction, Dpar);
	t_vec3 eye = vec3_substract(Pperp, Cperp);
	float a = vec3_dot(Dperp, Dperp);
	float b = vec3_dot(eye, Dperp) * 2.0;
	float c = vec3_dot(eye, eye) - (cp.radius * cp.radius);
	float	t[2];
	float delta;
	delta = sqrt((b * b) - (4.0 * a * c));
	if (delta <= 0)
		return (false);
	t[0] = (-b - delta) / (2.0 * a);
	t[1] = (-b + delta) / (2.0 * a);
	if (cp.size > 0 && vec3_length(vec3_substract(vec3_add(Ppar, vec3_scale(Dpar, t[0])), Cpar)) >= cp.size / 2)
		t[0] = 0;
	if (cp.size > 0 && vec3_length(vec3_substract(vec3_add(Ppar, vec3_scale(Dpar, t[1])), Cpar)) >= cp.size / 2)
		t[1] = 0;
	return (test_intersect(t, current_z));
}

//enum e_bool	intersect_cone(t_primitive cp, t_ray r, float *current_z)
//{
//	t_vec3	eye = vec3_substract(r.origin, cp.position);
//	float	a = vec3_dot(r.direction, r.direction) - (1 + cp.radius * cp.radius) * pow(vec3_dot(r.direction, cp.direction), 2);
//	float	b = 2.0 * vec3_dot(r.direction, eye) - (1 + cp.radius * cp.radius) * vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction);
//	float	c = vec3_dot(eye, eye) - (1 + cp.radius * cp.radius) * pow(vec3_dot(eye, cp.direction), 2);
//	//float	alpha = TO_RADIAN(cp.radius);
//	//float	a = pow(cos(alpha), 2) * (vec3_substract())
//	//float alpha = TO_RADIAN(cp.radius);
//	//t_vec3 eye = vec3_substract(r.origin, cp.position);
//	//t_vec3 tmp1 = vec3_substract(r.direction, vec3_scale(cp.direction, vec3_dot(r.direction, cp.direction)));
//	//t_vec3 tmp2 = vec3_substract(eye, vec3_scale(cp.direction, vec3_dot(eye, cp.direction)));
//	//float a = pow(cos(alpha), 2) * vec3_dot(tmp1, tmp1) - pow(sin(alpha), 2) * pow(vec3_dot(r.direction, cp.direction), 2);
//	//float b = 2.0 * (pow(cos(alpha), 2) * vec3_dot(tmp1, tmp2)) - 2.0 * (pow(sin(alpha), 2) * vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction));
//	//float c = pow(cos(alpha), 2) * vec3_dot(tmp2, tmp2) - pow(sin(alpha), 2) * pow(vec3_dot(eye, cp.direction), 2);
//	//t_vec3 eye = vec3_substract(r.origin, cp.position);
//	//float hangle = 1 + TO_RADIAN(cp.radius) * TO_RADIAN(cp.radius);
//	//float a   = vec3_dot(r.direction, r.direction) - hangle * pow(vec3_dot(r.direction, cp.direction), 2);
//	//float b   = 2 * (vec3_dot(r.direction, eye) - hangle * vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction));
//	//float c   = vec3_dot(eye, eye) - hangle * pow(vec3_dot(eye, cp.direction), 2);
//	//t_vec3 eye = vec3_substract(r.origin, cp.position);
//	//float radius = TO_RADIAN(cp.radius);
//	//float a = (cp.position.x * cp.position.x) + (cp.position.y * cp.position.y) - ((cp.position.z * cp.position.z) * radius);
//	//float b = 2.0 * (eye.x * cp.position.x + eye.y * cp.position.y - eye.z * cp.position.z * radius);
//	//float c = (eye.x * eye.x) + (eye.y * eye.y) - ((eye.z * eye.z) * radius);
//	//t_vec3 va = (t_vec3){0, -1, 0};
//	//float cos2a = cos(cp.radius);
//	//float sin2a = 1 - cos2a;
//	//t_vec3 eye = vec3_substract(r.origin, cp.position);
//	//float c1 = vec3_dot(r.direction, va);
//	//t_vec3 c2 = vec3_cross(va, r.direction);
//	//float c3 = vec3_dot(eye, va);
//	//t_vec3 c4 = vec3_scale(va, c3);
////
//	//float a = cos2a * vec3_length(vec3_substract(r.direction, c2)) - sin2a * c1 * c1;
//	//float b = 2.0 * cos2a * vec3_dot(vec3_substract(r.direction, c2), vec3_substract(eye, c4)) - 2.0 * sin2a * (c1 * c3);
//	//float c = cos2a * vec3_length(vec3_substract(eye, c4)) - sin2a * (c3 * c3);
////
//	//t_vec3 eye = vec3_substract(r.origin, cp.position);
//	//float tmp = (1 + TO_RADIAN(cp.radius) * TO_RADIAN(cp.radius));
//	//float a = vec3_dot(r.direction, r.direction);
//	//a = a - (tmp * pow(vec3_dot(r.direction, cp.direction), 2));
//	//float b = vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction);
//	//b = 2 * (vec3_dot(r.direction, eye) - b * tmp);
//	//float c = vec3_dot(eye, eye);
//	//c -= tmp * pow(vec3_dot(eye, cp.direction), 2);
//	float	t[2];
//	float	delta;
//	delta = sqrt((b * b) - (4.0 * a * c));
//	if (delta <= 0)
//		return (false);
//	t[0] = (-b - delta) / (2.0 * a);
//	t[1] = (-b + delta) / (2.0 * a);
//	return (test_intersect(t, current_z));
//}

enum e_bool	intersect_cone(t_primitive cp, t_ray r, float *current_z)
{
	float	a;
	float	b;
	float	c;
	float	tmp;
	t_vec3	eye;

	eye = vec3_substract(r.origin, cp.position);
	tmp = (1 + cp.radius * cp.radius);
	a = vec3_dot(r.direction, r.direction);
	a = a - (tmp * pow(vec3_dot(r.direction, cp.direction), 2));
	b = vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction);
	b = 2 * (vec3_dot(r.direction, eye) - b * tmp);
	c = vec3_dot(eye, eye);
	c -= tmp * pow(vec3_dot(eye, cp.direction), 2);
	float	t[2];
	float	delta;
	delta = sqrt((b * b) - (4.0 * a * c));
	if (delta <= 0)
		return (false);
	t[0] = (-b - delta) / (2.0 * a);
	t[1] = (-b + delta) / (2.0 * a);
	if (test_intersect(t, current_z))
	{
		eye = vec3_substract(vec3_add(r.origin, vec3_scale(r.direction, *current_z)), cp.position);
		if (cp.size == 0)// || cp.direction.x > 0)
			return (true);
		else if (cp.size > 0.
			&& vec3_dot(cp.direction, eye) > 0.
			&& (cp.size / cos(atan(cp.radius)) > vec3_length(eye)))
			return (true);
	}
	return (false);
}

enum e_bool	intersect_plane(t_primitive cp, t_ray r, float *current_z)
{
	float	m;
	float	t;
	float	d;
	t_vec3	eye;

	eye = vec3_substract(r.origin, cp.position);
	m = vec3_dot(cp.direction, eye);
	if (m < 0)
		return (false);
	d = vec3_dot(cp.direction, r.direction);
	t = -m / d;
	if (t <= 0)
		return (false);
	if (t < *(current_z) || *(current_z) == -1)
	{
		*current_z = t;
		return (true);
	}
	return (false);
}