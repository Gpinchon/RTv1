/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 19:36:51 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 20:25:20 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_zbuffer	*new_depth_buffer(t_point2 size)
{
	t_zbuffer *n;

	n = ft_memalloc(sizeof(t_zbuffer));
	n->size = size;
	n->buffer = ft_memalloc(sizeof(float*) * size.x);
	while (size.x)
	{
		n->buffer[size.x - 1] = ft_memalloc(sizeof(float) * n->size.y);
		while (size.y)
		{
			n->buffer[size.x - 1][size.y - 1] = -1;
			size.y--;
		}
		size.y = n->size.y;
		size.x--;
	}
	return (n);
}

void		*destroy_depth_buffer(t_zbuffer *d)
{
	if (!d || !d->buffer)
		return (d);
	while (d->size.x)
	{
		if (d->buffer[d->size.x - 1])
			free(d->buffer[d->size.x - 1]);
		d->size.x--;
	}
	free(d->buffer);
	free(d);
	return (NULL);
}

float		*get_current_z(t_zbuffer *depth,
	t_point2 screen_size, t_point2 current)
{
	return (&depth->buffer
		[(int)floor(depth->size.x / screen_size.x * current.x)]
		[(int)floor(depth->size.y / screen_size.y * current.y)]);
}
