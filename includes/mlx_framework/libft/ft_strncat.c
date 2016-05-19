/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:42:28 by gpinchon          #+#    #+#             */
/*   Updated: 2014/12/05 23:38:43 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, int n)
{
	char	*ptr;

	ptr = dest;
	while (*dest)
		dest++;
	while (*src && n)
	{
		*dest = *src;
		n--;
		dest++;
		src++;
	}
	*dest = '\0';
	return (ptr);
}
