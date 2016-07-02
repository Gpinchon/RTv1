/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 15:52:38 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 19:53:59 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	size_t	len;

	if (*to_find == '\0')
		return ((char *)str);
	len = ft_strlen(to_find);
	while (*str && len <= size--)
	{
		if (!ft_strncmp(str, to_find, len))
			return ((char *)str);
		str++;
	}
	return (NULL);
}
