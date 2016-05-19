#include "mlx_framework.h"
#include "internal_framework.h"

void	init_loop(t_framework *framework)
{
	if (framework)
		mlx_loop(framework->mlx_ptr);
}

void	*init_mlx_framework()
{
	t_framework	*framework;

	framework = ft_memalloc(sizeof(t_framework));
	framework->mlx_ptr = mlx_init();
	return (framework);
}

void	destroy_framework(t_framework *framework)
{
	destroy_windows(framework->windows);
	destroy_images(framework->images);
}

void	*get_mlx_ptr(t_framework *framework)
{
	return (framework->mlx_ptr);
}