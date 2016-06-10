#include "mlx_framework.h"
#include "internal_framework.h"

void	destroy_image(t_img *img)
{
	t_img *cimg;
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "In destroy_image\n");
	if ((cimg = (t_img*)img->prev))
		cimg->next = img->next;
	mlx_destroy_image(img->mlx_ptr, img->mlx_img);
	free(img);
}

void	destroy_images(t_img *from_img)
{
	t_img	*img[2];

	FRAMEWORK_DEBUG(!from_img, NULL_IMAGE_POINTER, "In destroy_images\n");
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

	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "In put_rgb_to_image\n");
	FRAMEWORK_DEBUG(
		p.x < 0 || p.x >= img->size.x
		|| p.y < 0 || p.y >= img->size.y,
		WRONG_IMAGE_COORD, "In put_rgb_to_image\n");
	i = p.x * img->opp + p.y * img->size_line;
	img->data[i] = c.b;
	img->data[i + 1] = c.g;
	img->data[i + 2] = c.r;
}

void	put_rgba_to_image(t_img *img, t_point2 p, t_rgba c)
{
	int i;

	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "In put_rgba_to_image\n");
	FRAMEWORK_DEBUG(
		p.x < 0 || p.x >= img->size.x
		|| p.y < 0 || p.y >= img->size.y,
		WRONG_IMAGE_COORD, "In put_rgba_to_image\n");
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
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "Im get_image_color\n");
	FRAMEWORK_DEBUG(i, WRONG_IMAGE_COORD, "Im get_image_color\n");
	i = p.x * img->opp + p.y * img->size_line;
	return ((t_rgb){img->data[i],
		img->data[i + 1],
		img->data[i + 2]});
}

void	*clear_image(t_img *img)
{
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "In clear_image\n");
	ft_memset(img->data, 0, (img->size.x * img->size.y) * img->opp);
	return (img);
}

void	*fill_image(t_img *img, t_rgb color)
{
	t_point2	buff;

	buff.y = 0;
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "In fill_image\n");
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
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "In add_image\n");
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "In add_image\n");
	if (!framework->images)
		return (framework->images = img);
	else
		return (append_object((void*)img, (void*)framework->images));
}

void	*new_image(t_framework *f, int width, int height, char *name)
{
	t_img	*img;

	FRAMEWORK_DEBUG(!f, NULL_FRAMEWORK_POINTER, "In new_image\n");
	FRAMEWORK_DEBUG(!f->mlx_ptr, NULL_MLX_POINTER, "In new_image\n");
	img = ft_memalloc(sizeof(t_img));
	FRAMEWORK_DEBUG(!img, MALLOC_ERROR, "In new_image\n");
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
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "In put_image_to_window\n");
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "In put_image_to_window\n");
	mlx_put_image_to_window (img->mlx_ptr, window->mlx_window, img->mlx_img, pos.x, pos.y);
	return (img);
}