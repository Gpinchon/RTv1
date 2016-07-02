/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 17:08:11 by gpinchon          #+#    #+#             */
/*   Updated: 2016/05/18 17:14:31 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float		clamp(float nbr, float min, float max)
{
	if (nbr >= max)
		return (max);
	else if (nbr <= min)
		return (min);
	else
		return (nbr);
}

long int	clamp_int(long int nbr, long int min, long int max)
{
	if (nbr >= max)
		return (max);
	else if (nbr <= min)
		return (min);
	else
		return (nbr);
}
