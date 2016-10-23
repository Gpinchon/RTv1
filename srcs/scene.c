/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 19:36:43 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/23 14:00:14 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	save_scene(int keycode, t_scene *scene)
{
	int fd;

	fd = open("scene.rtscene", O_CREAT | O_RDWR, S_IRWXU);
	write(fd, scene, sizeof(t_scene));
	write(fd, scene->primitive, sizeof(t_primitive) * scene->primitive_nbr);
	write(fd, scene->light, sizeof(t_light) * scene->light_nbr);
	close(fd);
	(void)keycode;
}

void	check_scene_read(UINT readsize, UINT expected)
{
	if (readsize != expected
	|| readsize >= MAX_OBJ)
	{
		ft_putstr("INVALID MAP !\n");
		exit(-42);
	}
}

t_scene	load_scene(const char *filepath)
{
	t_scene	s;
	char	dumy[1];
	int		fd;

	fd = open(filepath, O_RDONLY, 0);
	check_scene_read(read(fd, &s, sizeof(t_scene)), sizeof(t_scene));
	check_scene_read(read(fd,
		s.primitive = ft_memalloc(sizeof(t_primitive) * s.primitive_nbr),
		sizeof(t_primitive) * s.primitive_nbr),
		sizeof(t_primitive) * s.primitive_nbr);
	check_scene_read(read(fd,
		s.light = ft_memalloc(sizeof(t_light) * s.light_nbr),
		sizeof(t_light) * s.light_nbr),
		sizeof(t_light) * s.light_nbr);
	check_scene_read(read(fd, dumy, 1), 0);
	close(fd);
	return (s);
}

/*
** Why (void)v; ???
** Because : FUCK THE NORMINETTE !!!
** void	default_lights(t_scene *s)
** {
** 	s->light = ft_memalloc(sizeof(t_light) * 2);
** 	s->light[0] = new_light(DIRECTIONAL, (t_vec3[]){(t_vec3){1, 1, 0},
** 	(t_vec3){0, 0, 0}, (t_vec3){1, 1, 1}}, (float[]){1, 0.002, 200, 70, 1});
** 	s->light[1] = new_light(DIRECTIONAL, (t_vec3[]){(t_vec3){-1, -1, 0},
** 	(t_vec3){0, 0, 0}, (t_vec3){1, 1, 0.8}}, (float[]){0.3, 0.002, 200, 70, 0});
** 	s->light[2] = new_light(POINT, (t_vec3[]){(t_vec3){200, 50, 200},
** 	(t_vec3){0, 0, 0}, (t_vec3){1, 1, 0}}, (float[]){1, 0.002, 200, 80, 1});
** 	s->light[3] = new_light(POINT, (t_vec3[]){(t_vec3){-200, 50, 200},
** 	(t_vec3){0, 0, 0}, (t_vec3){1, 0, 1}}, (float[]){1, 0.002, 200, 80, 1});
** 	s->light[4] = new_light(POINT, (t_vec3[]){(t_vec3){-200, 50, -200},
** 	(t_vec3){0, 0, 0}, (t_vec3){0, 1, 1}}, (float[]){1, 0.002, 200, 80, 1});
** 	s->light[5] = new_light(POINT, (t_vec3[]){(t_vec3){200, 50, -200},
** 	(t_vec3){0, 0, 0}, (t_vec3){0, 0, 1}}, (float[]){1, 0.002, 200, 80, 1});
** 	s->light_nbr = 6;
** }
*/

void	default_lights(t_scene *s)
{
	t_vec3	v[0];

	(void)v;
	if (!(s->light = ft_memalloc(sizeof(t_light) * 6)))
	{
		s->light_nbr = 0;
		return ;
	}
	s->light[0] = new_light(DIRECTIONAL, (t_vec3[]){(t_vec3){1, 1, 0},
	(t_vec3){0, 0, 0}, (t_vec3){1, 1, 1}}, (float[]){1, 0.002, 200, 70, 1});
	s->light[1] = new_light(DIRECTIONAL, (t_vec3[]){(t_vec3){-1, -1, 0},
	(t_vec3){0, 0, 0}, (t_vec3){1, 1, .8}}, (float[]){.3, 0.002, 200, 70, 0});
	s->light[2] = new_light(POINT, (t_vec3[]){(t_vec3){200, 50, 200},
	(t_vec3){0, 0, 0}, (t_vec3){1, 1, 0}}, (float[]){1, 0.002, 200, 80, 1});
	s->light[3] = new_light(POINT, (t_vec3[]){(t_vec3){-200, 50, 200},
	(t_vec3){0, 0, 0}, (t_vec3){1, 0, 1}}, (float[]){1, 0.002, 200, 80, 1});
	s->light[4] = new_light(POINT, (t_vec3[]){(t_vec3){-200, 50, -200},
	(t_vec3){0, 0, 0}, (t_vec3){0, 1, 1}}, (float[]){1, 0.002, 200, 80, 1});
	s->light[5] = new_light(POINT, (t_vec3[]){(t_vec3){200, 50, -200},
	(t_vec3){0, 0, 0}, (t_vec3){0, 0, 1}}, (float[]){1, 0.002, 200, 80, 1});
	s->light_nbr = 6;
}

t_scene	default_scene(void)
{
	t_scene s;

	s.camera = new_camera((t_vec3){50, 0, -550}, (t_vec3){0, -50, 0},
		(t_vec3){0, 1, 0}, (t_vec2){TO_RADIAN(30), HEIGHT / (float)WIDTH});
	if (!(s.primitive = ft_memalloc(sizeof(t_primitive) * 3)))
	{
		default_lights(&s);
		s.primitive_nbr = 0;
		return (s);
	}
	s.primitive[0] = new_sphere((t_vec3){0, 100, 0}, 100);
	s.primitive[1] = new_cylinder((t_vec3){0, 100, 0},
		(t_vec3){0, 1, 0}, 101, 20);
	s.primitive[2] = new_cylinder((t_vec3){0, -50, 0},
		(t_vec3){0, 1, 0}, 10, 400);
	s.primitive[0].material = new_mtl((t_rgba){1, 0, 0, 1},
		(t_rgba){0.1, 0, 0, 1}, (t_rgba){1, 1, 1, 1}, (t_vec3){80, 0.2, 1});
	s.primitive[1].material = s.primitive[0].material;
	s.primitive[2].material = new_mtl((t_rgba){1, 1, 1, 1},
		(t_rgba){0, 0, 0, 1}, (t_rgba){1, 1, 1, 1}, (t_vec3){10, 1, 1});
	s.primitive_nbr = 3;
	default_lights(&s);
	ft_putstr("Lollipop ?\n");
	return (s);
}
