/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 14:18:46 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/24 16:31:04 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../adv_math.h"

t_vec3	vec3_normalize(t_vec3 v)
{
	double length;

	if ((length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z)))
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
	return (v);
}
