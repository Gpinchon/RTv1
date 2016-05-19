/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:20:11 by gpinchon          #+#    #+#             */
/*   Updated: 2014/11/08 19:09:11 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*buffer1;
	unsigned char			*buffer2;
	unsigned char			charc;

	buffer1 = (unsigned char*)dst;
	buffer2 = (unsigned char*)src;
	charc = (unsigned char)c;
	while (n--)
	{
		*buffer1 = *buffer2;
		if (*buffer1 == charc)
			return ((void*)(buffer1 + 1));
		buffer1++;
		buffer2++;
	}
	return (NULL);
}
