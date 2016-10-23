/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:20:11 by gpinchon          #+#    #+#             */
/*   Updated: 2016/04/05 15:19:08 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void			*ft_memcpy(void *str1, const void *str2, size_t n)
{
	char		*buffer1;
	const char	*buffer2;

	if (!n || str1 == str2)
		return (str1);
	buffer1 = str1;
	buffer2 = str2;
	while (n--)
		*buffer1++ = *buffer2++;
	return (str1);
}
