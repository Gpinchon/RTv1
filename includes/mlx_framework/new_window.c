/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 20:39:22 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/23 22:12:37 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_framework.h"
#include "internal_framework.h"

static void	*add_window(t_framework *framework, t_window *window)
{
	if (!framework->windows)
		return (framework->windows = window);
	else
		return (append_object((void*)window, (void*)framework->windows));
}

void	*new_window(t_framework *framework, int width, int height, char *name)
{
	t_window *win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "new_window");
	FRAMEWORK_DEBUG(!framework->mlx_ptr, NULL_MLX_POINTER, "new_window");
	win = ft_memalloc(sizeof(t_window));
	win->mlx_window = mlx_new_window(framework->mlx_ptr, width, height, name);
	win->mlx_ptr = framework->mlx_ptr;
	win->size = (t_point2){width, height};
	init_key_table(win->key, MAX_KEYS);
	keypress_callback(win, handle_keypress, win);
	return (add_window(framework, clear_window(win)));
}
