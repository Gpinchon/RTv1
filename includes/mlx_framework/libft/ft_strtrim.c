/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 15:53:26 by gpinchon          #+#    #+#             */
/*   Updated: 2014/12/05 23:39:54 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		lenwospace(const char *str)
{
	int	count;

	count = ft_strlen(str) - 1;
	while ((str[count] == ' ' || str[count] == '\n' || str[count] == '\t')
			&& count >= 0)
		count--;
	while ((*str == ' ' || *str == '\n' || *str == '\t')
			&& *str && count >= 0)
	{
		count--;
		str++;
	}
	return (count + 1);
}

char	*ft_strtrim(char const *s)
{
	unsigned int	len;
	char			*destination;

	if (s)
	{
		len = lenwospace(s);
		if ((destination = ft_strnew(len)) == NULL)
			return (NULL);
		while (*s)
		{
			if (*s != ' '
					&& *s != '\n'
					&& *s != '\t')
			{
				ft_strncpy(destination, s, len);
				destination[len] = '\0';
				return (destination);
			}
			s++;
		}
		return (destination);
	}
	return (NULL);
}
