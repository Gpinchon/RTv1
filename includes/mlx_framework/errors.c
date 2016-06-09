#include "mlx_framework.h"
#include "internal_framework.h"

void	init_errors()
{
	int i;

	i = 0;
	while (i < MAX_ERROR)
	{
		g_errors[i] = "Undefined error\n";
		i++;
	}
	g_errors[ALL_OK] = "All is ok !\n";
	g_errors[NULL_WINDOW_POINTER] = "Null window pointer\n";
	g_errors[NULL_IMAGE_POINTER] = "Null image pointer\n";
	g_errors[NULL_FRAMEWORK_POINTER] = "Null framework pointer\n";
	g_errors[NULL_MLX_POINTER] = "Null minilibx pointer\n";
	g_errors[MALLOC_ERROR] = "Malloc Error\n";
	g_errors[WRONG_IMAGE_COORD] = "Wrong image coordinates\n";
}

void	print_error(int error_code)
{
	if (error_code >= 0 && error_code < MAX_ERROR)
	{
		ft_putstr(g_errors[error_code]);
		return ;
	}
	ft_putstr("Incorrect error code : ");
	ft_putnbr(error_code);
	ft_putchar('\n');
}