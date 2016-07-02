/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framework.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:27:12 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/24 15:44:10 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_framework.h"
#include "internal_framework.h"

void	init_loop(t_framework *framework)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "init_loop");
	mlx_loop(framework->mlx_ptr);
}

void	*init_framework(void)
{
	t_framework	*framework;

	init_errors();
	framework = ft_memalloc(sizeof(t_framework));
	FRAMEWORK_DEBUG(!framework, MALLOC_ERROR, "init_framework");
	framework->mlx_ptr = mlx_init();
	FRAMEWORK_DEBUG(!framework->mlx_ptr, NULL_MLX_POINTER, "init_framework");
	return (framework);
}

void	destroy_framework(t_framework *framework)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "destroy_framework");
	if (framework->windows)
		destroy_windows(framework->windows);
	if (framework->images)
		destroy_images(framework->images);
	free(framework);
}

void	*get_mlx_ptr(t_framework *framework)
{
	return (framework->mlx_ptr);
}
