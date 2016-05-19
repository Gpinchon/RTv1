/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 15:44:12 by gpinchon          #+#    #+#             */
/*   Updated: 2016/03/19 16:40:11 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	wordlen(const char *str, char c)
{
	unsigned int len;

	len = 0;
	while (*str != c && *str)
	{
		len++;
		str++;
	}
	return (len);
}

char	*split_cpy(const char *str, char c)
{
	size_t	size;
	char	*strsplit;

	while (*str == c && *str)
		str++;
	size = wordlen(str, c);
	strsplit = ft_strnew(size);
	ft_strncpy(strsplit, str, size);
	strsplit[size] = '\0';
	return (strsplit);
}

size_t	wordcount(const char *str, char c)
{
	size_t size;

	size = 0;
	while (*str)
	{
		if (*str != c)
			size++;
		while (*str != c && *(str + 1))
			str++;
		str++;
	}
	return (size);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**split;
	size_t	i;

	if (s)
	{
		i = wordcount(s, c);
		split = ft_memalloc(sizeof(char**) * (i + 1));
		i = 0;
		while (*s)
		{
			if (*s != c)
			{
				split[i] = split_cpy(s, c);
				while (*s != c && *(s + 1))
					s++;
				i++;
			}
			s++;
		}
		split[i] = NULL;
		return (split);
	}
	return (NULL);
}
