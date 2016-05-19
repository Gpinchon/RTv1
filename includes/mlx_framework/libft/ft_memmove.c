/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:20:11 by gpinchon          #+#    #+#             */
/*   Updated: 2014/11/30 19:57:15 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *s1, const void *s2, size_t n)
{
	char	*buffer;

	buffer = malloc(n);
	if (s1 && s2 && buffer != NULL)
	{
		ft_memcpy(buffer, s2, n);
		ft_memcpy(s1, buffer, n);
	}
	free(buffer);
	return (s1);
}
