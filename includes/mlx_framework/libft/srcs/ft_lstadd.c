/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 18:54:14 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/12 19:56:41 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (!(*alst))
	{
		*alst = new;
		(*alst)->next = NULL;
		return ;
	}
	new->next = *alst;
	*alst = new;
}
