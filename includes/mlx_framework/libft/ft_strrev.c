/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 18:44:58 by gpinchon          #+#    #+#             */
/*   Updated: 2014/11/30 23:03:47 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	char	*p1;
	char	*p2;

	p1 = str;
	p2 = str;
	while (*p2)
		p2++;
	p2--;
	while (p1 < p2)
		ft_charswap(p1++, p2--);
	return (str);
}
