#include "mlx_framework.h"
#include "internal_framework.h"

void	loop_callback(t_framework *framework, int (*fun)(), void *arg)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "In loop_callback\n");
	mlx_loop_hook(framework->mlx_ptr, fun, arg);
}

void	expose_callback(t_window *window, int (*fun)(), void *arg)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "In expose_callback\n");
	mlx_expose_hook(window->mlx_window, fun, arg);
}

void	mouse_callback(t_window *window, int (*fun)(), void *arg)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "In mouse_callback\n");
	mlx_mouse_hook(window->mlx_window, fun, arg);
}

void	keypress_callback(t_window *window, int (*fun)(), void *arg)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "In key_callback\n");
	mlx_hook(window->mlx_window, KEYPRESS, 0, fun, arg);
}

void	init_key_table(t_key *table, int max_keys)
{
	while (max_keys)
	{
		table[max_keys].callback = NULL;
		table[max_keys].arg = NULL;
		max_keys--;
	}
}

int		handle_keypress(int keycode, t_window *window)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "In key_callback\n");
	FRAMEWORK_DEBUG(keycode < 0 || keycode >= MAX_KEYS, INVALID_KEYCODE,
		"In key_callback\n");
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

void	setup_keypress(t_window *window, int keycode, void (*keyfun)(), void *arg)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "In key_callback\n");
	if (keycode >= 0 && keycode < MAX_KEYS)
	{
		window->key[keycode].callback = keyfun;
		window->key[keycode].arg = arg;
	}
}