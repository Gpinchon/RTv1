/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 19:14:23 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 19:23:43 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../adv_math.h"

t_vec3				vec3_rotx(const t_vec3 vec, const float r)
{
	float			cos_r;
	float			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = vec.x;
	ret.y = cos_r * vec.y - sin_r * vec.z;
	ret.z = sin_r * vec.y + cos_r * vec.z;
	return (ret);
}

t_vec3				vec3_roty(const t_vec3 vec, const float r)
{
	float			cos_r;
	float			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = sin_r * vec.z + cos_r * vec.x;
	ret.y = vec.y;
	ret.z = cos_r * vec.z - sin_r * vec.x;
	return (ret);
}

t_vec3				vec3_rotz(const t_vec3 vec, const float r)
{
	float			cos_r;
	float			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = cos_r * vec.x - sin_r * vec.y;
	ret.y = sin_r * vec.x + cos_r * vec.y;
	ret.z = vec.z;
	return (ret);
}

t_vec3				vec3_rot(const t_vec3 vec, const t_vec3 vec1)
{
	t_vec3			ret;

	ret = vec3_rotx(vec, vec1.x);
	ret = vec3_roty(vec, vec1.y);
	return (vec3_rotz(vec, vec1.z));
}
