/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 14:16:19 by gpinchon          #+#    #+#             */
/*   Updated: 2016/05/06 14:41:09 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*file_to_str(int fd)
{
	char	*ret;
	char	*l;

	ret = NULL;
	while (get_next_line(fd, &l) > 0)
	{
		ret = ft_strjoin(ret, l);
		ret = ft_strjoin(ret, "\n");
		free(l);
	}
	return (ret);
}
