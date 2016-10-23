/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/06 12:32:09 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 16:48:51 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char		*ft_strjoinfree(char **a, char **b)
{
	char	*joined;

	joined = ft_strjoin(*a, *b);
	ft_strdel(a);
	ft_strdel(b);
	return (joined);
}

static int		get_single_line(const int fd, char **save)
{
	int		value;
	char	*buffer;

	while (!ft_strchr(*save, '\n'))
	{
		buffer = (char *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1));
		if ((value = read(fd, buffer, BUFF_SIZE)) < 0)
			return (value);
		*save = ft_strjoinfree(save, &buffer);
		if (!value)
		{
			if (**save)
				return (1);
			return (0);
		}
	}
	return (1);
}

static char		*ft_strndup(const char *s, size_t n)
{
	char	*str;
	char	*ptr;

	str = (char *)malloc(sizeof(char) * ft_strlen(s));
	ptr = str;
	while (*s && n--)
		*ptr++ = *s++;
	*ptr = '\0';
	return (str);
}

static int		check_er(const int fd, char **line)
{
	return (fd < 0 || !line ? -1 : 1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*save = NULL;
	static int	last_fd = 0;
	int			value;
	char		*tmp;

	save = last_fd != fd ? NULL : save;
	tmp = save ? ft_strdup(save) : NULL;
	if (check_er(fd, line) == -1 || (value = get_single_line(fd, &tmp)) == -1)
		return (-1);
	if (!ft_strchr(tmp, '\n') || !value)
	{
		*line = tmp && *tmp ? ft_strdup(tmp) : NULL;
		ft_strdel(&save);
	}
	else
	{
		*line = ft_strndup(tmp, ft_strlen(tmp) -
			ft_strlen(ft_strchr(tmp, '\n')));
		ft_strdel(&save);
		save = ft_strdup(ft_strchr(tmp, '\n') + 1);
	}
	ft_strdel(&tmp);
	last_fd = fd;
	return (value);
}
