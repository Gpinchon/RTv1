/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtlightcreate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 21:27:35 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 21:28:34 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_mtl	new_mtl(t_rgba dif, t_rgba amb, t_rgba spec, t_vec3 factors)
{
	t_mtl material;

	material.diffuse = dif;
	material.ambient = amb;
	material.specular = spec;
	material.spec_power = factors.x;
	material.roughness = factors.y;
	material.albedo = factors.z;
	return (material);
}

t_light	new_light(int type, t_vec3 pdc[3], float factors[6])
{
	t_light	l;

	l.type = type;
	l.position = pdc[0];
	l.direction = pdc[1];
	l.color = (t_rgb){pdc[2].x, pdc[2].y, pdc[2].z};
	l.power = factors[0];
	l.attenuation = factors[1];
	l.falloff = factors[2];
	l.spot_size = factors[3];
	l.specular = factors[4];
	return (l);
}
