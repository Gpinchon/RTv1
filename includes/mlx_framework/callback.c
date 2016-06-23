/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 20:30:05 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/23 20:30:35 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_framework.h"
#include "internal_framework.h"

void	loop_callback(t_framework *framework, int (*fun)(), void *arg)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "loop_callback");
	mlx_loop_hook(framework->mlx_ptr, fun, arg);
}

void	expose_callback(t_window *window, int (*fun)(), void *arg)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "expose_callback");
	mlx_expose_hook(window->mlx_window, fun, arg);
}

void	mouse_callback(t_window *window, int (*fun)(), void *arg)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "mouse_callback");
	mlx_mouse_hook(window->mlx_window, fun, arg);
}

void	keypress_callback(t_window *window, int (*fun)(), void *arg)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "key_callback");
	mlx_hook(window->mlx_window, KEYPRESS, KEYPRESSMASK, fun, arg);
}
