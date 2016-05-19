/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 15:51:11 by gpinchon          #+#    #+#             */
/*   Updated: 2014/12/05 21:10:57 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*string;
	int		count;

	if (s == NULL || f == NULL || !s || !f)
		return (NULL);
	count = 0;
	if (s && f)
	{
		string = ft_strdup(s);
		if (string == NULL)
			return (NULL);
		while (string[count] != '\0')
		{
			string[count] = f(s[count]);
			count++;
		}
		return (string);
	}
	return ((char*)s);
}
