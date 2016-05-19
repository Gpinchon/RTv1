/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:20:11 by gpinchon          #+#    #+#             */
/*   Updated: 2014/11/08 16:48:48 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	char	*s1;
	char	c1;

	s1 = (char*)s;
	c1 = (unsigned char)c;
	while (n--)
	{
		if (*s1 == c1)
			return (s1);
		if (!s1)
			return (NULL);
		s1++;
	}
	return (NULL);
}
