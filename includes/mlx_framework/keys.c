/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 20:30:43 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/24 15:46:36 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_framework.h"
#include "internal_framework.h"

void	init_key_table(t_key *table, int max_keys)
{
	max_keys--;
	while (max_keys)
	{
		table[max_keys].callback = NULL;
		table[max_keys].arg = NULL;
		max_keys--;
	}
}

int		handle_keypress(int keycode, t_window *window)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "key_callback");
	FRAMEWORK_DEBUG(keycode < 0 || keycode >= MAX_KEYS, INVALID_KEYCODE,
		"key_callback");
	if (keycode >= 0
	&& keycode < MAX_KEYS
	&& window->key[keycode].callback)
	{
		if (window->key[keycode].arg)
			window->key[keycode].callback(keycode, window->key[keycode].arg);
		else
			window->key[keycode].callback(keycode);
		return (1);
	}
	return (0);
}

void	setup_keypress(t_window *window, int keycode,
	void (*keyfun)(), void *arg)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "key_callback");
	if (keycode >= 0 && keycode < MAX_KEYS)
	{
		window->key[keycode].callback = keyfun;
		window->key[keycode].arg = arg;
	}
}

int		refresh_window(t_window *window)
{
	if (!window)
		return (NULL_WINDOW_POINTER);
	if (!window->attached_image)
		return (NULL_IMAGE_POINTER);
	put_image_to_window(window->attached_image, window, (t_point2){0, 0});
	return (ALL_OK);
}
