#include "mlx_framework.h"
#include "internal_framework.h"

int		attach_image_to_window(t_img *img, t_window *window)
{
	if (!window)
		return (NULL_WINDOW_POINTER);
	if (!img)
		return (NULL_IMAGE_POINTER);
	window->attached_image = img;
	return (ALL_OK);
}

int		put_rgb_to_window(t_window *window, t_point2 p, t_rgb c)
{
	if (!window)
		return (NULL_WINDOW_POINTER);
	else if (!window->attached_image)
		return (NULL_IMAGE_POINTER);
	put_rgb_to_image(window->attached_image, p, c);
	return (ALL_OK);
}

void	destroy_window(t_window *window)
{
	t_window	*win;

	if ((win = (t_window *)window->prev))
		win->next = window->next;
	mlx_destroy_window(window->mlx_ptr, window->mlx_window);
	free(window);
}

void	destroy_windows(t_window *windows)
{
	t_window	*win[2];

	win[0] = windows;
	while (win[0])
	{
		win[1] = win[0]->next;
		destroy_window(win[0]);
		win[0] = win[1];
	}
}

void	*clear_window(t_window *window)
{
	mlx_clear_window(window->mlx_ptr, window->mlx_window);
	return (window);
}

void	*add_window(t_framework *framework, t_window *window)
{
	if (!framework->windows)
		return (framework->windows = window);
	else
		return (append_object((void*)window, (void*)framework->windows));
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

void	*new_window(t_framework *framework, int width, int height, char *name)
{
	t_window *win;

	if (!framework || !framework->mlx_ptr)
	{
		FRAMEWORK_DEBUG(!framework ? NULL_FRAMEWORK_POINTER : NULL_MLX_POINTER);
		return (NULL);
	}
	win = ft_memalloc(sizeof(t_window));
	win->mlx_window = mlx_new_window(framework->mlx_ptr, width, height, name);
	win->mlx_ptr = framework->mlx_ptr;
	win->size = (t_point2){width, height};
	return (add_window(framework, clear_window(win)));
}