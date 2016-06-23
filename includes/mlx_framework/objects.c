/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:56:10 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/23 22:16:48 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_framework.h"
#include "internal_framework.h"

void	destroy_objects(t_generic *from_object)
{
	t_generic	*obj[2];

	obj[0] = from_object;
	FRAMEWORK_DEBUG(!from_object, NULL_OBJECT_POINTER, "destroy_objects");
	while (obj[0])
	{
		obj[1] = obj[0]->next;
		free(obj[0]);
		obj[0] = obj[1];
	}
}

void	*append_object(t_generic *new_object, t_generic *from_object)
{
	FRAMEWORK_DEBUG(!from_object, NULL_OBJECT_POINTER, "append_object");
	FRAMEWORK_DEBUG(!new_object, NULL_OBJECT_POINTER, "append_object");
	while (from_object->next)
		from_object = from_object->next;
	new_object->prev = from_object;
	return (from_object->next = new_object);
}
