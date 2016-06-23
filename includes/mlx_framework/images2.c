/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 20:33:12 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/23 20:33:57 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_framework.h"
#include "internal_framework.h"

void	*clear_image(t_img *img)
{
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "clear_image");
	ft_memset(img->data, 0, (img->size.x * img->size.y) * img->opp);
	return (img);
}

void	*fill_image(t_img *img, t_rgb color)
{
	t_point2	buff;

	buff.y = 0;
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "fill_image");
	while (buff.y < img->size.y)
	{
		buff.x = 0;
		while (buff.x < img->size.x)
		{
			put_rgb_to_image(img, buff, color);
			buff.x++;
		}
		buff.y++;
	}
	return (img);
}

void	*add_image(t_framework *framework, t_img *img)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "add_image");
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "add_image");
	if (!framework->images)
		return (framework->images = img);
	else
		return (append_object((void*)img, (void*)framework->images));
}

void	*new_image(t_framework *f, int width, int height, char *name)
{
	t_img	*img;

	FRAMEWORK_DEBUG(!f, NULL_FRAMEWORK_POINTER, "new_image");
	FRAMEWORK_DEBUG(!f->mlx_ptr, NULL_MLX_POINTER, "new_image");
	img = ft_memalloc(sizeof(t_img));
	FRAMEWORK_DEBUG(!img, MALLOC_ERROR, "new_image");
	img->mlx_img = mlx_new_image(f->mlx_ptr, width, height);
	img->data = mlx_get_data_addr(img->mlx_img, &img->bpp,
		&img->size_line, &img->endian);
	img->size = (t_point2){width, height};
	img->opp = img->bpp / 8;
	img->mlx_ptr = f->mlx_ptr;
	img->name = name;
	return (add_image(f, clear_image(img)));
}

void	*put_image_to_window(t_img *img, t_window *window, t_point2 pos)
{
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "put_image_to_window");
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "put_image_to_window");
	mlx_put_image_to_window (img->mlx_ptr, window->mlx_window,
		img->mlx_img, pos.x, pos.y);
	return (img);
}
