/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 20:32:56 by gpinchon          #+#    #+#             */
/*   Updated: 2016/03/31 17:22:40 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	cycle_float(float nbr, float min, float max)
{
	if (nbr > max)
		return (min);
	else if (nbr < min)
		return (max);
	else
		return (nbr);
}

int		cycle_int(int nbr, int min, int max)
{
	if (nbr > max)
		return (min);
	else if (nbr < min)
		return (max);
	else
		return (nbr);
}
