/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:02:52 by gpinchon          #+#    #+#             */
/*   Updated: 2014/11/06 19:30:53 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_bzero(void *s, size_t n)
{
	int		count;
	char	*buffer;

	count = 0;
	buffer = s;
	while (n--)
		buffer[count++] = '\0';
	return (s);
}
