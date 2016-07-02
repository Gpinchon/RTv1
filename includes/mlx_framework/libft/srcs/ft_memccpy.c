/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:20:11 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 18:23:49 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	UCHAR	*buffer1;
	UCHAR	*buffer2;
	UCHAR	charc;

	buffer1 = (UCHAR*)dst;
	buffer2 = (UCHAR*)src;
	charc = (UCHAR)c;
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
