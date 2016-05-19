/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 15:53:11 by gpinchon          #+#    #+#             */
/*   Updated: 2015/12/23 12:39:18 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*destination;

	if (s)
	{
		destination = ft_strnew(len);
		if (destination == NULL)
			return (NULL);
		while (start--)
			s++;
		ft_strncpy(destination, s, len);
		destination[len] = '\0';
		return (destination);
	}
	else
		return (NULL);
}
