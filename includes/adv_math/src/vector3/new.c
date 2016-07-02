/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 16:31:46 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/24 16:31:57 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../adv_math.h"

t_vec3	new_vec3(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	vec2_to_vec3(t_vec2 v)
{
	return ((t_vec3){v.x, v.y, 0});
}

t_vec3	vec4_to_vec3(t_vec4 v)
{
	return ((t_vec3){v.x, v.y, v.z});
}
