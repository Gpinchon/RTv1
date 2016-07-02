/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 17:33:11 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 20:13:15 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	while (n)
	{
		if (*s1 != *s2)
			return ((*(UCHAR *)s1 - *(UCHAR *)s2));
		if (!*s1)
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
