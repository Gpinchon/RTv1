/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/06 19:09:41 by gpinchon          #+#    #+#             */
/*   Updated: 2015/12/23 12:35:20 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	int res;
	int count;
	int neg;

	res = 0;
	count = 0;
	neg = 0;
	while (str[count] == ' ' || str[count] == '\t' || str[count] == '\n'
			|| str[count] == '\v' || str[count] == '\f' || str[count] == '\r')
		count++;
	if (str[count] == '-' || str[count] == '+')
	{
		(str[count] == '-') ? neg = 1 : count;
		count++;
	}
	while (str[count] >= '0' && str[count] <= '9' && str[count] != '\0')
	{
		res = res * 10 + str[count] - '0';
		count++;
	}
	if (neg == 1)
		return (-res);
	return (res);
}
