#include "mlx_framework.h"
#include "internal_framework.h"

void	loop_callback(t_framework *framework, int (*fun)(), void *arg)
{
	if (framework)
		mlx_loop_hook(framework->mlx_ptr, fun, arg);
}

void	expose_callback(t_window *window, int (*fun)(), void *arg)
{
	if (window)
		mlx_expose_hook(window->mlx_window, fun, arg);
}

void	mouse_callback(t_window *window, int (*fun)(), void *arg)
{
	if (window)
		mlx_mouse_hook(window->mlx_window, fun, arg);
}

void	key_callback(t_window *window, int (*fun)(), void *arg)
{
	if (window)
		mlx_expose_hook(window->mlx_window, fun, arg);
}