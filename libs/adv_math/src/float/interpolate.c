/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 14:18:46 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/24 16:34:14 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../adv_math.h"

float	float_lerp(float start, float end, float percent)
{
	percent = (percent > 1.f) ? 1.f : percent;
	percent = (percent < 0.f) ? 0.f : percent;
	return (((end - start) * percent) + start);
}

float	float_smoothlerp(float start, float end, float amount)
{
	amount = (amount > 1.f) ? 1.f : amount;
	amount = (amount < 0.f) ? 0.f : amount;
	amount = amount * amount * (3.f - (2.f * amount));
	return (((end - start) * amount) + start);
}

float	float_step(float a, float x)
{
	return (x >= a);
}
