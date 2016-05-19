/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 17:02:41 by gpinchon          #+#    #+#             */
/*   Updated: 2015/04/29 17:04:04 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*null(char *s)
{
	char			*str;

	str = ft_memalloc(ft_strlen(s) + 1);
	ft_strcpy(str, s);
	return (str);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;

	if (!s1 && s2)
		return (null((char*)s2));
	else if (!s2 && s1)
		return (null((char*)s1));
	else if (s1 && s2)
	{
		str = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (str == NULL)
			return (NULL);
		ft_strcpy(str, s1);
		ft_strcat(str, s2);
		return (str);
	}
	return (NULL);
}
