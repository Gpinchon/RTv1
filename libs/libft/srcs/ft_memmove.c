/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:20:11 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 20:24:29 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	if (!n)
		return (s1);
	else if (!s2 && !s1)
		return (NULL);
	s = (unsigned char *)s2;
	d = (unsigned char *)s1;
	if (s < d)
	{
		s = s + n;
		d = d + n;
		while (n--)
			*--d = *--s;
	}
	else
		ft_memcpy(d, s, n);
	return (s1);
}
