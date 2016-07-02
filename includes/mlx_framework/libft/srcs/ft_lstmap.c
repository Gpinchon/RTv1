/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 18:56:45 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 19:57:29 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*n;
	t_list	*sn;

	if (!(n = ft_memalloc(sizeof(t_list))))
		return (NULL);
	n = f(lst);
	sn = n;
	while (lst->next)
	{
		if (!(n->next = ft_memalloc(sizeof(t_list))))
			return (NULL);
		lst = lst->next;
		n->next = f(lst);
		n = n->next;
	}
	return (sn);
}
