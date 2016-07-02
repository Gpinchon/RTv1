/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 20:32:56 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 16:53:29 by gpinchon         ###   ########.fr       */
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
