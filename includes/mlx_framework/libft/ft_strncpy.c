/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:42:38 by gpinchon          #+#    #+#             */
/*   Updated: 2014/12/02 15:09:58 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*destination;

	destination = dest;
	while (*src && n)
	{
		*destination++ = *src++;
		n--;
	}
	while (n--)
		*destination++ = '\0';
	return (dest);
}
