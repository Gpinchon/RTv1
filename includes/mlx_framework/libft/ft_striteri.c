/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 15:50:40 by gpinchon          #+#    #+#             */
/*   Updated: 2014/12/02 15:54:38 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int index;

	index = 0;
	if (f)
	{
		while (*s)
			f(index++, s++);
	}
}
