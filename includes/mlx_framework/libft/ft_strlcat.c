/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:42:47 by gpinchon          #+#    #+#             */
/*   Updated: 2014/11/30 19:40:12 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		destlen;
	size_t		srclen;

	destlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (destlen > (size - 1) || !size)
		return (srclen + size);
	while (size > 1 && *dst)
	{
		dst++;
		size--;
	}
	while (size > 1 && *src)
	{
		*(dst++) = *(src++);
		size--;
	}
	*dst = '\0';
	return (destlen + srclen);
}
