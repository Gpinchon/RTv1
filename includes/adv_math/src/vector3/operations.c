/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/20 14:46:34 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 19:17:53 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../adv_math.h"

t_vec3	vec3_project(t_vec3 v, t_vec3 v1)
{
	return (vec3_scale(v1, vec3_dot(v, v1) / vec3_dot(v1, v1)));
}

t_vec3	vec3_add(t_vec3 vector1, t_vec3 vector2)
{
	return ((t_vec3){
		vector1.x + vector2.x,
		vector1.y + vector2.y,
		vector1.z + vector2.z
	});
}

t_vec3	vec3_substract(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	});
}

t_vec3	vec3_multiply(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z
	});
}

t_vec3	vec3_cross(t_vec3 vector1, t_vec3 vector2)
{
	return ((t_vec3){
		vector1.y * vector2.z - vector1.z * vector2.y,
		vector1.z * vector2.x - vector1.x * vector2.z,
		vector1.x * vector2.y - vector1.y * vector2.x
	});
}
