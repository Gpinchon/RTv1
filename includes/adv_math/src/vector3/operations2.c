/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 19:15:59 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 19:17:50 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../adv_math.h"

t_vec3	vec3_divide(t_vec3 v, t_vec3 v1)
{
	return ((t_vec3){
		v.x / v1.x,
		v.y / v1.y,
		v.z / v1.z
	});
}

t_vec3	vec3_scale(t_vec3 v, float d)
{
	return ((t_vec3){
		v.x * d,
		v.y * d,
		v.z * d
	});
}

t_vec3	vec3_fdivide(t_vec3 v, float d)
{
	return ((t_vec3){
		v.x / d,
		v.y / d,
		v.z / d
	});
}

t_vec3	vec3_fadd(t_vec3 v, float d)
{
	return ((t_vec3){
		v.x + d,
		v.y + d,
		v.z + d
	});
}

t_vec3	vec3_abs(t_vec3 v)
{
	return ((t_vec3){
		fabs(v.x),
		fabs(v.y),
		fabs(v.z)
	});
}
