/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/10 16:01:08 by gpinchon          #+#    #+#             */
/*   Updated: 2016/04/26 20:11:06 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	c = 0;
	if (to_find[0] == '\0')
		return (char*)(str);
	while (str[i] != '\0')
	{
		j = i;
		c = 0;
		while (str[j] == to_find[c])
		{
			j++;
			c++;
			if (to_find[c] == '\0')
				return (char*)(&str[i]);
		}
		i++;
	}
	return (NULL);
}