/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_framework.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 18:24:26 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/23 22:18:55 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_FRAMEWORK_H
# define MLX_FRAMEWORK_H
# include "./keys.h"
# define UCHAR		unsigned char
# define UINT		unsigned int
# define GSTRUCT	struct s_generic

/*
** Error codes
*/
# define MAX_ERROR				16
# define ALL_OK					0x0
# define NULL_WINDOW_POINTER	0x1
# define NULL_IMAGE_POINTER		0x2
# define NULL_FRAMEWORK_POINTER	0x3
# define NULL_MLX_POINTER		0x4
# define MALLOC_ERROR			0x5
# define WRONG_IMAGE_COORD		0x6
# define NO_WINDOWS				0x7
# define NULL_OBJECT_POINTER	0x8
# define INVALID_KEYCODE		0x9

char	*g_errors[MAX_ERROR];

# ifdef DEBUG
# include <assert.h>
#  define FRAMEWORK_DEBUG(cond, c, fn)	if(cond){print_error(c, fn);}
# else
#  define FRAMEWORK_DEBUG(cond, c, fn)
# endif

# pragma pack (1)

typedef struct	s_point2
{
	int			x;
	int			y;
}				t_point2;

typedef struct	s_rgb
{
	float		r;
	float		g;
	float		b;
}				t_rgb;

typedef struct	s_rgba
{
	float		r;
	float		g;
	float		b;
	float		a;
}				t_rgba;

typedef struct	s_generic
{
	GSTRUCT		*next;
	GSTRUCT		*prev;
	char		*name;
	void		*mlx_ptr;
}				t_generic;

typedef struct	s_img
{
	void		*next;
	void		*prev;
	char		*name;
	void		*mlx_ptr;
	void		*mlx_img;
	char		*data;
	t_point2	size;
	int			bpp;
	int			opp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_key
{
	void		(*callback)();
	void		*arg;
}				t_key;

typedef struct	s_window
{
	void		*next;
	void		*prev;
	char		*name;
	void		*mlx_ptr;
	void		*mlx_window;
	void		*attached_image;
	t_key		key[MAX_KEYS + 1];
	t_point2	size;
}				t_window;

typedef struct	s_framework
{
	void		*mlx_ptr;
	void		*windows;
	void		*images;
}				t_framework;

# pragma pack ()

/*
** Window tools
*/
void			*clear_window(t_window *window);
void			*new_window(t_framework *f, int width, int height, char *name);
void			*destroy_window(t_framework *framework, t_window *window);
void			destroy_windows(t_framework *framework);
void			attach_image_to_window(t_img *img, t_window *window);
void			put_rgb_to_window(t_window *window, t_point2 p, t_rgb c);
int				refresh_window(t_window *window);
/*
** Image tools
*/
t_rgb			get_image_color(t_img *img, t_point2 p);
void			put_rgb_to_image(t_img *img, t_point2 p, t_rgb c);
void			put_rgba_to_image(t_img *img, t_point2 p, t_rgba c);
void			*clear_image(t_img *img);
void			*fill_image(t_img *img, t_rgb color);
void			*new_image(t_framework *f, int width, int height, char *name);
void			*put_image_to_window(t_img *img, t_window *win, t_point2 pos);
void			destroy_image(t_img *img);
void			destroy_images(t_img *from_img);
/*
** Object management tools
*/
void			destroy_objects(t_generic *from_object);
void			*append_object(t_generic *new_object, t_generic *from_object);
/*
** Framework tools
*/
void			init_loop(t_framework *framework);
void			*init_framework();
void			destroy_framework(t_framework *framework);
void			*get_mlx_ptr(t_framework *framework);
/*
** Error Management
*/
void			init_errors();
void			print_error(int error_code, const char *function_name);
/*
** Callback functions
*/
void			loop_callback(t_framework *framework, int (*fun)(), void *arg);
void			expose_callback(t_window *window, int (*fun)(), void *arg);
void			mouse_callback(t_window *window, int (*fun)(), void *arg);
void			setup_keypress(t_window *window, int keycode, void (*keyfun)(), void *arg);
/*
** Color tools
*/
t_rgba			rgb_to_rgba(t_rgb a);
t_rgba			rgba_add(t_rgba a, t_rgba b);
t_rgba			rgba_multiply(t_rgba a, t_rgba b);
t_rgba			rgba_scale(t_rgba a, double b);
t_rgb			rgba_to_rgb(t_rgba a);
t_rgb			rgb_add(t_rgb a, t_rgb b);
t_rgb			rgb_multiply(t_rgb a, t_rgb b);
t_rgb			rgb_scale(t_rgb a, double b);
t_rgb			rgb_divide(t_rgb a, double b);
#endif
