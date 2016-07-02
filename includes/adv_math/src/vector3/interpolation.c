/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 14:18:46 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/24 16:30:43 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../adv_math.h"

t_vec3	vec3_lerp(t_vec3 start, t_vec3 end, float percent)
{
	return ((t_vec3){
		percent * (end.x - start.x) + start.x,
		percent * (end.y - start.y) + start.y,
		percent * (end.z - start.z) + start.z
	});
}

t_vec3	vec3_smoothlerp(t_vec3 start, t_vec3 end, float percent)
{
	amount = (amount > 1.f) ? 1.f : amount;
	amount = (amount < 0.f) ? 0.f : amount;
	amount = amount * amount * (3.f - (2.f * amount));
	return ((t_vec3){
		(amount * (end.x - start.x)) + start.x,
		(amount * (end.y - start.y)) + start.y,
		(amount * (end.z - start.z)) + start.z
	});
}

t_vec3	vec3_slerp(t_vec3 start, t_vec3 end, float percent)
{
	float	dot;
	float	theta;
	t_vec3	rel_vec;

	dot = clamp(vec3_dot(start, end), -1, 1);
	theta = acos(dot) * percent;
	rel_vec = vec3_normalize(vec3_fmultiply(vec3_substract(end, start), dot));
	return (vec3_add(vec3_fmultiply(start, cos(theta)),
		vec3_fmultiply(rel_vec, sin(theta))));
}

t_vec3	vec3_nlerp(t_vec3 start, t_vec3 end, float percent)
{
	return (vec3_normalize(vec3_lerp(start, end, percent)));
}
