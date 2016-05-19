/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 15:52:38 by gpinchon          #+#    #+#             */
/*   Updated: 2015/12/23 12:39:04 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	char *index;
	char *index2;

	if (!*to_find)
		return ((char*)str);
	index2 = (char*)to_find;
	while (*str && size)
	{
		if (*str == *index2)
		{
			index = (char*)str;
			while (*to_find == *str && size-- && *to_find && *str)
			{
				to_find++;
				str++;
			}
			if (!*to_find)
				return (index);
			to_find = index2;
		}
		size--;
		str++;
	}
	return (NULL);
}
