/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordcount.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 16:54:30 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 16:55:32 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t			wordcount(const char *str, char c)
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
