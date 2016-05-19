/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:20:11 by gpinchon          #+#    #+#             */
/*   Updated: 2014/11/08 17:16:41 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned	char *s1;
	unsigned	char *s2;

	s1 = (unsigned char*)str1;
	s2 = (unsigned char*)str2;
	while (n--)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
