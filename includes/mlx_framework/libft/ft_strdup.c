/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:20:11 by gpinchon          #+#    #+#             */
/*   Updated: 2015/12/23 12:37:48 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char				*ft_strdup(const char *str)
{
	char			*str_copy;
	unsigned int	size;
	unsigned int	count;

	str_copy = NULL;
	count = 0;
	size = (int)ft_strlen(str);
	str_copy = (char *)malloc(sizeof(char) * (size + 1));
	if (str_copy == NULL)
		return (NULL);
	while (count != size)
	{
		str_copy[count] = str[count];
		count++;
	}
	str_copy[count] = '\0';
	return (str_copy);
}
