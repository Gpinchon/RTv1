/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 18:39:44 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 19:57:45 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*n;

	if (!(n = ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		n->content = NULL;
		n->content_size = 0;
		return (n);
	}
	if (content_size && !(n->content = ft_memalloc(content_size)))
		return (NULL);
	n->content = ft_memcpy(n->content, content, content_size);
	n->content_size = content_size;
	return (n);
}
