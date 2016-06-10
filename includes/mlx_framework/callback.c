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

void	key_callback(t_window *window, int (*fun)(), void *arg)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "In key_callback\n");
	mlx_key_hook(window->mlx_window, fun, arg);
}