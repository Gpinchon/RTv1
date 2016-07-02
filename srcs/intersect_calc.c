/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 21:01:32 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 21:01:51 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

enum e_bool	test_intersect(float t[2], float *current_z)
{
	enum e_bool	retvalue;

	retvalue = false;
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

void		float_swap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

enum e_bool	solve_quadratic(float a, float b, float c, float *t)
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
