#include "mlx_framework.h"
#include "internal_framework.h"

void	attach_image_to_window(t_img *img, t_window *window)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "In attach_image_to_window\n");
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "In attach_image_to_window\n");
	window->attached_image = img;
}

void	put_rgb_to_window(t_window *window, t_point2 p, t_rgb c)
{
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "In put_rgb_to_window\n");
	FRAMEWORK_DEBUG(!window->attached_image, NULL_IMAGE_POINTER,
		"In put_rgb_to_window\n");
	put_rgb_to_image(window->attached_image, p, c);
}

void	*destroy_window(t_framework *framework, t_window *window)
{
	GSTRUCT	*win;

	win = NULL;
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "In destroy_window\n");
	FRAMEWORK_DEBUG(!window->mlx_ptr, NULL_MLX_POINTER, "In destroy_window\n");
	FRAMEWORK_DEBUG(!framework, NULL_WINDOW_POINTER, "In destroy_window\n");
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

	FRAMEWORK_DEBUG(!f, NULL_FRAMEWORK_POINTER, "In destroy_windows\n");
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
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "In clear_window\n");
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

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "In new_window\n");
	FRAMEWORK_DEBUG(!framework->mlx_ptr, NULL_MLX_POINTER, "In new_window\n");
	win = ft_memalloc(sizeof(t_window));
	win->mlx_window = mlx_new_window(framework->mlx_ptr, width, height, name);
	win->mlx_ptr = framework->mlx_ptr;
	win->size = (t_point2){width, height};
	init_key_table(win->key, MAX_KEYS);
	keypress_callback(win, handle_keypress, win);
	return (add_window(framework, clear_window(win)));
}