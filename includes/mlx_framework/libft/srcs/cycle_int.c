/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 16:53:40 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 16:56:13 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		cycle_int(int nbr, int min, int max)
{
	if (nbr > max)
		return (min);
	else if (nbr < min)
		return (max);
	else
		return (nbr);
}
