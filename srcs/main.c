/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 20:46:53 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/23 19:50:48 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	init_rt(t_rt *rt)
{
	rt->scene.primitive = NULL;
	rt->scene.light = NULL;
	rt->scene.primitive_nbr = 0;
	rt->scene.light_nbr = 0;
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
	assign_keypress_hook(rt->framework, rt->window, SDL_SCANCODE_ESCAPE, new_callback(exit_rt, rt));
	assign_keypress_hook(rt->framework, rt->window, SDL_SCANCODE_LEFT, new_callback(move_along_x, rt));
	assign_keypress_hook(rt->framework, rt->window, SDL_SCANCODE_RIGHT, new_callback(move_along_x, rt));
	assign_keypress_hook(rt->framework, rt->window, SDL_SCANCODE_KP_PLUS, new_callback(move_along_y, rt));
	assign_keypress_hook(rt->framework, rt->window, SDL_SCANCODE_KP_MINUS, new_callback(move_along_y, rt));
	assign_keypress_hook(rt->framework, rt->window, SDL_SCANCODE_UP, new_callback(move_along_z, rt));
	assign_keypress_hook(rt->framework, rt->window, SDL_SCANCODE_DOWN, new_callback(move_along_z, rt));
	assign_keypress_hook(rt->framework, rt->window, SDL_SCANCODE_S, new_callback(save_scene, &rt->scene));
}

int		main(int argc, const char **argv)
{
	t_rt	rt;

	init_rt(&rt);
	if (argc > 1)
		rt.scene = load_scene(argv[1]);
	else
	{
		ft_putstr("Please specify a map !\nCreating default scene...\n");
		rt.scene = default_scene();
	}
	rt.framework = new_framework();
	rt.window = new_window(rt.framework, WIDTH, HEIGHT, "RTv1");
	rt.image = new_image(rt.framework, WIDTH, HEIGHT);
	rt.depth = new_depth_buffer((t_point2){1, 1});
	attach_image_to_window(rt.image, rt.window);
	fill_image(rt.image, &(rgb(BACKGROUND.r, BACKGROUND.g, BACKGROUND.b)));
	refresh_window(rt.window);
	init_keys(&rt);
	assign_loop_hook(rt.framework, new_callback(refresh_window, rt.window));
	do_raytracer((t_point2){WIDTH, HEIGHT}, rt);
	init_loop(rt.framework);
	return (0);
}
