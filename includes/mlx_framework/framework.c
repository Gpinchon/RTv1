#include "mlx_framework.h"
#include "internal_framework.h"

int		init_loop(t_framework *framework)
{
	if (framework)
		mlx_loop(framework->mlx_ptr);
	return (framework ? ALL_OK : NULL_FRAMEWORK_POINTER);
}

void	*init_mlx_framework()
{
	t_framework	*framework;

	init_errors();
	if (!(framework = ft_memalloc(sizeof(t_framework))))
	{
		FRAMEWORK_DEBUG(MALLOC_ERROR);
		return (NULL);
	}
	framework->mlx_ptr = mlx_init();
	return (framework);
}

int		destroy_framework(t_framework *framework)
{
	if (!framework)
		return (NULL_FRAMEWORK_POINTER);
	if (framework->windows)
		destroy_windows(framework->windows);
	else
		return (NULL_WINDOW_POINTER);
	if (framework->images)
		destroy_images(framework->images);
	else
		return(NULL_IMAGE_POINTER);
	return (ALL_OK);
}

void	*get_mlx_ptr(t_framework *framework)
{
	return (framework->mlx_ptr);
}