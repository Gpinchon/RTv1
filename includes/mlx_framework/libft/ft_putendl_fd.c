/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 19:08:19 by gpinchon          #+#    #+#             */
/*   Updated: 2014/11/25 19:10:07 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putendl_fd(char const *s, int fd)
{
	ft_putstr_fd((char *)s, fd);
	ft_putchar_fd('\n', fd);
}
