/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:30:20 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/23 20:39:24 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_framework.h"
#include "internal_framework.h"

void	attach_image_to_window(t_img *img, t_window *window)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "attach_image_to_window");
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "attach_image_to_window");
	window->attached_image = img;
}

void	put_rgb_to_window(t_window *window, t_point2 p, t_rgb c)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "put_rgb_to_window");
	FRAMEWORK_DEBUG(!window->attached_image, NULL_IMAGE_POINTER,
		"put_rgb_to_window");
	put_rgb_to_image(window->attached_image, p, c);
}

void	*destroy_window(t_framework *framework, t_window *window)
{
	GSTRUCT	*win;

	win = NULL;
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "destroy_window");
	FRAMEWORK_DEBUG(!window->mlx_ptr, NULL_MLX_POINTER, "destroy_window");
	FRAMEWORK_DEBUG(!framework, NULL_WINDOW_POINTER, "destroy_window");
	if (window == framework->windows)
		framework->windows = window->next;
	if ((win = (GSTRUCT *)window->prev))
	{
		win->next = window->next;
		win->next->prev = win;
	}
	else if ((win = (GSTRUCT *)window->next))
		win->prev = NULL;
	mlx_destroy_window(window->mlx_ptr, window->mlx_window);
	free(window);
	return (win);
}

void	destroy_windows(t_framework *f)
{
	t_window	*win[2];

	FRAMEWORK_DEBUG(!f, NULL_FRAMEWORK_POINTER, "destroy_windows");
	win[0] = (t_window *)f->windows;
	while (win[0])
	{
		win[1] = win[0]->next;
		destroy_window(f, win[0]);
		win[0] = win[1];
	}
}

void	*clear_window(t_window *window)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "clear_window");
	mlx_clear_window(window->mlx_ptr, window->mlx_window);
	return (window);
}
