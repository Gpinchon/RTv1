#include "mlx_framework.h"
#include "internal_framework.h"

void	init_errors()
{
	int i;

	i = 0;
	while (i < MAX_ERROR)
	{
		g_errors[i] = "Undefined error";
		i++;
	}
	g_errors[ALL_OK] = "All is ok";
	g_errors[NULL_WINDOW_POINTER] = "Null window pointer";
	g_errors[NULL_IMAGE_POINTER] = "Null image pointer";
	g_errors[NULL_FRAMEWORK_POINTER] = "Null framework pointer";
	g_errors[NULL_MLX_POINTER] = "Null minilibx pointer";
	g_errors[MALLOC_ERROR] = "Malloc Error";
	g_errors[WRONG_IMAGE_COORD] = "Wrong image coordinates";
	g_errors[NO_WINDOWS] = "No windows found";
	g_errors[INVALID_KEYCODE] = "Invalid keycode";
}

void	print_error(int error_code, const char *function_name)
{
	if (error_code >= 0 && error_code < MAX_ERROR)
		ft_putstr(g_errors[error_code]);
	else
	{
		ft_putstr("Incorrect error code : ");
		ft_putnbr(error_code);
	}
	ft_putstr(" in ");
	ft_putendl((char*)function_name);
}