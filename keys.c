/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 19:29:43 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/23 22:21:28 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	exit_rt(int key, t_rt *rt)
{
	destroy_framework(rt->framework);
	destroy_depth_buffer(rt->depth);
	ft_putstr("kthxbye !\n");
	free(rt->scene.primitive);
	free(rt->scene.light);
	exit(key);
}

void	move_along_x(int key, t_rt *rt)
{
	rt->scene.camera.position.x += key == LEFTARROW ? 50 : -50;
	rt->scene.camera = update_camera(rt->scene.camera, HEIGHT / (float)WIDTH);
	do_raytracer((t_point2){WIDTH, HEIGHT}, *rt);
	refresh_window(rt->window);
}

void	move_along_y(int key, t_rt *rt)
{
	rt->scene.camera.position.y += key == KEYPADPLUS ? 50 : -50;
	rt->scene.camera = update_camera(rt->scene.camera, HEIGHT / (float)WIDTH);
	do_raytracer((t_point2){WIDTH, HEIGHT}, *rt);
	refresh_window(rt->window);
}

void	move_along_z(int key, t_rt *rt)
{
	rt->scene.camera.position.z += key == UPARROW ? 50 : -50;
	rt->scene.camera = update_camera(rt->scene.camera, HEIGHT / (float)WIDTH);
	do_raytracer((t_point2){WIDTH, HEIGHT}, *rt);
	refresh_window(rt->window);
}
