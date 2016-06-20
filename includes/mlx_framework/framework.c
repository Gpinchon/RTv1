#include "mlx_framework.h"
#include "internal_framework.h"

void	init_loop(t_framework *framework)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "In init_loop\n");
	mlx_loop(framework->mlx_ptr);
}

void	*init_framework()
{
	t_framework	*framework;

	init_errors();
	framework = ft_memalloc(sizeof(t_framework));
	FRAMEWORK_DEBUG(!framework, MALLOC_ERROR, "In init_framework\n");
	framework->mlx_ptr = mlx_init();
	FRAMEWORK_DEBUG(!framework->mlx_ptr, NULL_MLX_POINTER, "In init_framework\n");
	return (framework);
}

void	destroy_framework(t_framework *framework)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "In destroy_framework\n");
	if (framework->windows)
		destroy_windows(framework->windows);
	if (framework->images)
		destroy_images(framework->images);
}

void	*get_mlx_ptr(t_framework *framework)
{
	return (framework->mlx_ptr);
}