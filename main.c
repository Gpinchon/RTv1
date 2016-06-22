/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 20:46:53 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/22 21:28:50 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	init_rt(t_rt *rt)
{
	rt->intersect[SPHERE] = intersect_sphere;
	rt->intersect[CYLINDER] = intersect_cylinder;
	rt->intersect[CONE] = intersect_cone;
	rt->intersect[PLANE] = intersect_plane;
	rt->normal[SPHERE] = sphere_normal;
	rt->normal[CYLINDER] = cylinder_normal;
	rt->normal[CONE] = cone_normal;
	rt->normal[PLANE] = plane_normal;
}

void	init_keys(t_rt *rt)
{
	setup_keypress(rt->window, ESCAPE, exit_rt, rt);
	setup_keypress(rt->window, LEFTARROW, move_along_x, rt);
	setup_keypress(rt->window, RIGHTARROW, move_along_x, rt);
	setup_keypress(rt->window, KEYPADPLUS, move_along_y, rt);
	setup_keypress(rt->window, KEYPADMINUS, move_along_y, rt);
	setup_keypress(rt->window, UPARROW, move_along_z, rt);
	setup_keypress(rt->window, DOWNARROW, move_along_z, rt);
	setup_keypress(rt->window, S_KEY, save_scene, &rt->scene);
}

int		main(int argc, const char **argv)
{
	t_rt	rt;

	if (argc > 1)
		rt.scene = load_scene(argv[1]);
	else
	{
		ft_putstr("Please specify a map !\nCreating default scene...\n");
		rt.scene = default_scene();
	}
	rt.framework = init_framework();
	rt.window = new_window(rt.framework, WIDTH, HEIGHT, "RTv1");
	rt.image = new_image(rt.framework, WIDTH, HEIGHT, "display");
	rt.depth = new_depth_buffer((t_point2){1, 1});
	init_rt(&rt);
	attach_image_to_window(rt.image, rt.window);
	fill_image(rt.image, rgb_scale(BACKGROUND, 255));
	refresh_window(rt.window);
	init_keys(&rt);
	loop_callback(rt.framework, refresh_window, rt.window);
	do_raytracer((t_point2){WIDTH, HEIGHT}, rt);
	init_loop(rt.framework);
	return (0);
}
