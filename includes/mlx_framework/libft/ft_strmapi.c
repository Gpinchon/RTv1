/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 15:51:27 by gpinchon          #+#    #+#             */
/*   Updated: 2014/12/05 19:48:40 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*string;
	char			*str;

	if (!s || !f || s == NULL || f == NULL)
		return (NULL);
	index = 0;
	if (s && f)
	{
		string = ft_strdup(s);
		str = string;
		while (*string)
		{
			*string = f(index++, *string);
			string++;
		}
		return (str);
	}
	return ((char*)s);
}
