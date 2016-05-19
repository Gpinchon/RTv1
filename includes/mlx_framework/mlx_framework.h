# define UCHAR unsigned char

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

#pragma pack (1)
typedef struct	s_generic
{
	void		*next;
	void		*prev;
	char		*name;
	void		*mlx_ptr;
}				t_generic;

#pragma pack (1)
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

#pragma pack (1)
typedef struct	s_window
{
	void		*next;
	void		*prev;
	char		*name;
	void		*mlx_ptr;
	void		*mlx_window;
	void		*attached_image;
	t_point2	size;
}				t_window;

typedef struct	s_framework
{
	void		*mlx_ptr;
	void		*windows;
	void		*images;
}				t_framework;

/*
** Window tools
*/
void	*clear_window(t_window *window);
void	*new_window(t_framework *framework, int width, int height, char *name);
void	*add_window(t_framework *framework, t_window *window);
void	destroy_window(t_window *window);
void	destroy_windows(t_window *from_windows);
int		attach_image_to_window(t_img *img, t_window *window);
int		put_rgb_to_window(t_window *window, t_point2 p, t_rgb c);
int		refresh_window(t_window *window);
/*
** Image tools
*/
t_rgb	get_image_color(t_img *img, t_point2 p);
void	put_rgb_to_image(t_img *img, t_point2 p, t_rgb c);
void	put_rgba_to_image(t_img *img, t_point2 p, t_rgba c);
void	*clear_image(t_img *img);
void	*fill_image(t_img *img, t_rgb color);
void	*new_image(t_framework *framework, int width, int height, char *name);
void	*put_image_to_window(t_img *img, t_window *window, t_point2 pos);
void	destroy_image(t_img *img);
void	destroy_images(t_img *from_img);
/*
** Object management tools
*/
void	destroy_objects(t_generic *from_object);
void	*append_object(t_generic *new_object, t_generic *from_object);
/*
** Framework tools
*/
void	init_loop(t_framework *framework);
void	*init_mlx_framework();
void	destroy_framework(t_framework *framework);
void	*get_mlx_ptr(t_framework *framework);
/*
** Callback functions
*/
void	loop_callback(t_framework *framework, int (*fun)(), void *arg);
void	expose_callback(t_window *window, int (*fun)(), void *arg);
void	mouse_callback(t_window *window, int (*fun)(), void *arg);
void	key_callback(t_window *window, int (*fun)(), void *arg);
/*
** Color tools
*/
t_rgba	rgb_to_rgba(t_rgb a);
t_rgba	rgba_add(t_rgba a, t_rgba b);
t_rgba	rgba_multiply(t_rgba a, t_rgba b);
t_rgba	rgba_scale(t_rgba a, double b);
t_rgb	rgba_to_rgb(t_rgba a);
t_rgb	rgb_add(t_rgb a, t_rgb b);
t_rgb	rgb_multiply(t_rgb a, t_rgb b);
t_rgb	rgb_scale(t_rgb a, double b);
t_rgb	rgb_divide(t_rgb a, double b);