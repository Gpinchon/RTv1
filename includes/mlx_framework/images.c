#include "mlx_framework.h"
#include "internal_framework.h"

int		destroy_image(t_img *img)
{
	t_img *cimg;
	if (!img)
		return(NULL_IMAGE_POINTER);
	if ((cimg = (t_img*)img->prev))
		cimg->next = img->next;
	mlx_destroy_image(img->mlx_ptr, img->mlx_img);
	free(img);
	return (ALL_OK);
}

int		destroy_images(t_img *from_img)
{
	t_img	*img[2];

	if (!from_img)
		return(NULL_IMAGE_POINTER);
	img[0] = from_img;
	while (img[0])
	{
		img[1] = img[0]->next;
		destroy_image(img[0]);
		img[0] = img[1];
	}
	return (ALL_OK);
}

int		put_rgb_to_image(t_img *img, t_point2 p, t_rgb c)
{
	int i;

	if (!img)
		return (NULL_IMAGE_POINTER);
	if (p.x < 0 || p.x >= img->size.x || p.y < 0 || p.y >= img->size.y)
		return (WRONG_IMAGE_COORD);
	i = p.x * img->opp + p.y * img->size_line;
	img->data[i] = c.b;
	img->data[i + 1] = c.g;
	img->data[i + 2] = c.r;
	return (ALL_OK);
}

int		put_rgba_to_image(t_img *img, t_point2 p, t_rgba c)
{
	int i;

	if (!img)
		return (NULL_IMAGE_POINTER);
	if (p.x < 0 || p.x >= img->size.x || p.y < 0 || p.y >= img->size.y)
		return (WRONG_IMAGE_COORD);
	i = p.x * img->opp + p.y * img->size_line;
	img->data[i] = c.b;
	img->data[i + 1] = c.g;
	img->data[i + 2] = c.r;
	img->data[i + 2] = c.a;
	return (ALL_OK);
}

t_rgb	get_image_color(t_img *img, t_point2 p)
{
	int		i;

	if (!img)
	{
		FRAMEWORK_DEBUG(NULL_IMAGE_POINTER);
		return((t_rgb){-1, -1, -1});
	}
	if (p.x < 0 || p.x >= img->size.x || p.y < 0 || p.y >= img->size.y)
	{
		FRAMEWORK_DEBUG(WRONG_IMAGE_COORD);
		return ((t_rgb){-1, -1, -1});
	}
	i = p.x * img->opp + p.y * img->size_line;
	return ((t_rgb){img->data[i],
		img->data[i + 1],
		img->data[i + 2]});
}

void	*clear_image(t_img *img)
{
	if (!img)
		FRAMEWORK_DEBUG(NULL_IMAGE_POINTER);
	ft_memset(img->data, 0, (img->size.x * img->size.y) * img->opp);
	return (img);
}

void	*fill_image(t_img *img, t_rgb color)
{
	t_point2	buff;

	buff.y = 0;
	if (!img)
	{
		FRAMEWORK_DEBUG(NULL_IMAGE_POINTER);
		return (NULL);
	}
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
	if (!framework || !img)
	{
		if (!framework)
			FRAMEWORK_DEBUG(NULL_FRAMEWORK_POINTER);
		if (!img)
			FRAMEWORK_DEBUG(NULL_IMAGE_POINTER);
		return (NULL);
	}
	if (!framework->images)
		return (framework->images = img);
	else
		return (append_object((void*)img, (void*)framework->images));
}

void	*new_image(t_framework *f, int width, int height, char *name)
{
	t_img	*img;

	img = NULL;
	if (!f || !f->mlx_ptr)
	{
		FRAMEWORK_DEBUG(!f ? NULL_FRAMEWORK_POINTER : NULL_MLX_POINTER);
		return (NULL);
	}
	if (!(img = ft_memalloc(sizeof(t_img))))
	{
		FRAMEWORK_DEBUG(MALLOC_ERROR);
		return (NULL);
	}
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
	if (!img || !window)
	{
		if (!img)
			FRAMEWORK_DEBUG(NULL_IMAGE_POINTER);
		if (!window)
			FRAMEWORK_DEBUG(NULL_WINDOW_POINTER);
		return (NULL);
	}
	mlx_put_image_to_window (img->mlx_ptr, window->mlx_window, img->mlx_img, pos.x, pos.y);
	return (img);
}