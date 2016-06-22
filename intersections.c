# include <rt.h>
#include <stdio.h>


enum e_bool	test_intersect(float t[2], float *current_z)
{
	enum e_bool	retvalue;

	retvalue = false;
	//if ((t[0] < 0 && t[1] > 0) || (t[0] > 0 && t[1] < 0))
	//	return (false);
	if ((t[0] > DOUBLE_ZERO)
	&& (t[0] < *(current_z) || *current_z == -1))
	{
		*(current_z) = t[0];
		retvalue = true;
	}
	if (!float_equal(t[0], t[1])
	&& (t[1] > DOUBLE_ZERO) 
	&& (t[1] < *(current_z) || *current_z == -1))
	{
		*(current_z) = t[1];
		retvalue = true;
	}
	return (retvalue);
}

void	float_swap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

enum e_bool solve_quadratic(float a, float b, float c, float *t)
{
	float	discrim;
	float	q;

	discrim = (b * b - 4.f * a * c);
	if (discrim <= 0)
		return (false);
	discrim = sqrtf(discrim);
	if (b < 0)
		q = -.5f * (b - discrim);
	else
		q = -.5f * (b + discrim);
	t[0] = q / a;
	t[1] = c / q;
	if (t[0] > t[1])
		float_swap(&t[0], &t[1]);
	return (true);
}

enum e_bool	intersect_sphere(t_primitive s, t_ray r, float *current_z)
{
	t_vec3 eye = vec3_substract(r.origin, s.position);
	float	a = vec3_dot(r.direction, r.direction);
	float	b = vec3_dot(eye, r.direction) * 2.0;
	float	c = vec3_dot(eye, eye) - (s.radius2);
	float	t[2];
	return (solve_quadratic(a, b, c, t) && test_intersect(t, current_z));
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
	float c = vec3_dot(eye, eye) - (cp.radius2);
	float	t[2];
	float delta;
	delta = (b * b) - (4.0 * a * c);
	if (delta <= 0)
		return (false);
	delta = sqrt(delta);
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
	float c = vec3_dot(eye, eye) - (cp.radius2);
	float	t[2];
	float delta;
	delta = (b * b) - (4.0 * a * c);
	if (delta <= 0)
		return (false);
	delta = sqrt(delta);
	t[0] = (-b - delta) / (2.0 * a);
	t[1] = (-b + delta) / (2.0 * a);
	if (cp.size > 0
		&& vec3_length(vec3_substract(vec3_add(Ppar, vec3_scale(Dpar, t[0])), Cpar)) >= cp.size / 2)
		t[0] = 0;
	if (cp.size > 0
		&& vec3_length(vec3_substract(vec3_add(Ppar, vec3_scale(Dpar, t[1])), Cpar)) >= cp.size / 2)
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

//enum e_bool	intersect_cone(t_primitive cp, t_ray r, float *current_z)
//{
//	float	a;
//	float	b;
//	float	c;
//	float	tmp;
//	t_vec3	eye;
//	float	tmp_z;
//
//	eye = vec3_substract(r.origin, cp.position);
//	tmp = (1 + cp.radius2);
//	a = vec3_dot(r.direction, r.direction);
//	a = a - (tmp * pow(vec3_dot(r.direction, cp.direction), 2));
//	b = vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction);
//	b = 2 * (vec3_dot(r.direction, eye) - b * tmp);
//	c = vec3_dot(eye, eye);
//	c -= tmp * pow(vec3_dot(eye, cp.direction), 2);
//	float	t[2];
//	tmp_z = *(current_z);
//	if (solve_quadratic(a, b, c, t) && (test_intersect(t, &tmp_z)))
//	{
//		eye = vec3_substract(vec3_add(r.origin, vec3_scale(r.direction, *current_z)), cp.position);
//		if (cp.size == 0)// || cp.direction.x > 0)
//		{
//			*(current_z) = tmp_z;
//			return (true);
//		}
//		else if (cp.size > 0.
//			&& vec3_dot(cp.direction, eye) > 0.
//			&& (cp.size / cos(atan(cp.radius)) > vec3_length(eye)))
//		{
//			*(current_z) = tmp_z;
//			return (true);
//		}
//	}
//	return (false);
//}

//enum e_bool	intersect_cone(t_primitive cp, t_ray r, float *current_z)
//{
//	float	a;
//	float	b;
//	float	c;
//	float	tmp;
//	t_vec3	eye;
//
//	eye = vec3_substract(r.origin, cp.position);
//	tmp = (1 + cp.radius * cp.radius);
//	a = vec3_dot(r.direction, r.direction);
//	a = a - (tmp * pow(vec3_dot(r.direction, cp.direction), 2));
//	b = vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction);
//	b = 2 * (vec3_dot(r.direction, eye) - b * tmp);
//	c = vec3_dot(eye, eye);
//	c -= tmp * pow(vec3_dot(eye, cp.direction), 2);
//	float	t[2];
//	float	delta;
//	delta = (b * b) - (4.0 * a * c);
//	if (delta <= 0)
//		return (false);
//	delta = sqrt(delta);
//	t[0] = (-b - delta) / (2.0 * a);
//	t[1] = (-b + delta) / (2.0 * a);
//	if (test_intersect(t, current_z))
//	{
//		eye = vec3_substract(vec3_add(r.origin, vec3_scale(r.direction, *current_z)), cp.position);
//		if (cp.size == 0)// || cp.direction.x > 0)
//		{
//			return (true);
//		}
//		else if (cp.size > 0.
//			&& vec3_dot(cp.direction, eye) > 0.
//			&& (cp.size / cos(atan(cp.radius)) > vec3_length(eye)))
//		{
//			return (true);
//		}
//	}
//	return (false);
//}

enum e_bool	intersect_cone(t_primitive cp, t_ray r, float *current_z)
{
	float	a;
	float	b;
	float	c;
	t_vec3	eye;
	float	t[2], tmp_z;
	t_vec3	tmp1, tmp2;

	eye = vec3_substract(r.origin, cp.position);
	tmp1 = vec3_substract(r.direction, vec3_scale(cp.direction, vec3_dot(r.direction, cp.direction)));
	tmp2 = vec3_substract(eye, vec3_scale(cp.direction, vec3_dot(eye, cp.direction)));
	a = pow(cos(cp.radius), 2) * vec3_dot(tmp1, tmp1) -
			pow(sin(cp.radius), 2) * pow(vec3_dot(r.direction, cp.direction), 2);
	b = 2 * (pow(cos(cp.radius), 2) * vec3_dot(tmp1, tmp2)) -
		2 * (pow(sin(cp.radius), 2) * vec3_dot(r.direction, cp.direction) * vec3_dot(eye, cp.direction));
	c = pow(cos(cp.radius), 2) * vec3_dot(tmp2, tmp2) - pow(sin(cp.radius), 2) *
			pow(vec3_dot(eye, cp.direction), 2);
	tmp_z = *(current_z);
	if (solve_quadratic(a, b, c, t) && (test_intersect(t, &tmp_z)))
	{
		//if (!test_intersect(t, &tmp_z))
		//	return (false);
		eye = vec3_substract(vec3_add(r.origin, vec3_scale(r.direction, tmp_z)), cp.position);
		if (cp.size == 0)// || cp.direction.x > 0)
		{
			*(current_z) = tmp_z;
			return (true);
		}
		else if (cp.size > 0.
			&& vec3_dot(cp.direction, eye) > 0.)
			if ((cp.size / cos(atan(cp.radius)) > vec3_length(eye)))
			{
				*(current_z) = tmp_z;
				return (true);
			}
	}
	return (false);
}

enum e_bool	intersect_plane(t_primitive cp, t_ray r, float *current_z)
{
	t_vec3	normal = vec3_negate(cp.direction);
	float denom = vec3_dot(normal, r.direction); 
	if (denom > 1e-6)
	{ 
		t_vec3 p0l0 = vec3_substract(cp.position, r.origin); 
		float t = vec3_dot(p0l0, normal) / denom; 
		if (t >= 0
		&& (t <= *(current_z) || *(current_z) == -1))
		{
			*current_z = t;
			return (true);
		}
	}
	return false; 
	//float	m;
	//float	t;
	//float	d;
	//t_vec3	eye;
//
	//eye = vec3_substract(r.origin, cp.position);
	//m = vec3_dot(cp.direction, eye);
	//if (m < 0)
	//	return (false);
	//d = vec3_dot(cp.direction, r.direction);
	//t = -m / d;
	//if (t <= 0)
	//	return (false);
	//if (t <= *(current_z) || *(current_z) == -1)
	//{
	//	*current_z = t;
	//	return (true);
	//}
	//return (false);
}