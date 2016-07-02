/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 16:20:10 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 18:21:10 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	intlenght(int n)
{
	size_t	size;

	size = 1;
	if (n < 0)
		size++;
	while ((n /= 10))
		size++;
	return (size);
}

static char		*isneg(int n, char *str, char *ptr)
{
	n *= -1;
	while (n)
	{
		*(ptr++) = '0' + (n % 10);
		n /= 10;
	}
	*ptr = '-';
	*(ptr + 1) = '\0';
	return (ft_strrev(str));
}

char			*ft_itoa(int n)
{
	char			*str;
	char			*ptr;

	if (!(str = (char *)ft_memalloc(sizeof(char) * (intlenght(n) + 1))))
		return (NULL);
	ptr = str;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		return (isneg(n, str, ptr));
	if (!n)
		*ptr = '0';
	if (n < 10)
	{
		*str = n + 48;
		return (str);
	}
	while (n)
	{
		*(ptr++) = '0' + (n % 10);
		n /= 10;
	}
	return (ft_strrev(str));
}
