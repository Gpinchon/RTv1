/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:56:10 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/23 20:33:02 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_framework.h"
#include "internal_framework.h"

void	destroy_image(t_img *img)
{
	t_img *cimg;
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "destroy_image");
	if ((cimg = (t_img*)img->prev))
		cimg->next = img->next;
	mlx_destroy_image(img->mlx_ptr, img->mlx_img);
	free(img);
}

void	destroy_images(t_img *from_img)
{
	t_img	*img[2];

	FRAMEWORK_DEBUG(!from_img, NULL_IMAGE_POINTER, "destroy_images");
	img[0] = from_img;
	while (img[0])
	{
		img[1] = img[0]->next;
		destroy_image(img[0]);
		img[0] = img[1];
	}
}

void	put_rgb_to_image(t_img *img, t_point2 p, t_rgb c)
{
	int i;

	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "put_rgb_to_image");
	FRAMEWORK_DEBUG(
		p.x < 0 || p.x >= img->size.x
		|| p.y < 0 || p.y >= img->size.y,
		WRONG_IMAGE_COORD, "put_rgb_to_image");
	i = p.x * img->opp + p.y * img->size_line;
	img->data[i] = c.b;
	img->data[i + 1] = c.g;
	img->data[i + 2] = c.r;
}

void	put_rgba_to_image(t_img *img, t_point2 p, t_rgba c)
{
	int i;

	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "put_rgba_to_image");
	FRAMEWORK_DEBUG(
		p.x < 0 || p.x >= img->size.x
		|| p.y < 0 || p.y >= img->size.y,
		WRONG_IMAGE_COORD, "put_rgba_to_image");
	i = p.x * img->opp + p.y * img->size_line;
	img->data[i] = c.b;
	img->data[i + 1] = c.g;
	img->data[i + 2] = c.r;
	img->data[i + 2] = c.a;
}

t_rgb	get_image_color(t_img *img, t_point2 p)
{
	int		i;

	i = p.x < 0 || p.x >= img->size.x || p.y < 0 || p.y >= img->size.y;
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "Im get_image_color");
	FRAMEWORK_DEBUG(i, WRONG_IMAGE_COORD, "Im get_image_color");
	i = p.x * img->opp + p.y * img->size_line;
	return ((t_rgb){img->data[i],
		img->data[i + 1],
		img->data[i + 2]});
}
