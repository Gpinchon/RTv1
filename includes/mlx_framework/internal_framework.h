/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_framework.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 14:18:46 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/20 16:54:41 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_MLX_H
# define INTERNAL_MLX_H
# include <mlx.h>
# include <libft.h>
# include <stdlib.h>

int		handle_keypress(int keycode, t_window *window);
void	init_key_table(t_key *table, int max_keys);
void	keypress_callback(t_window *window, int (*fun)(), void *arg);;

#endif
