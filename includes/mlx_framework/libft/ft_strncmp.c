/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 17:33:11 by gpinchon          #+#    #+#             */
/*   Updated: 2015/12/23 12:38:12 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *string1, const char *string2, int n)
{
	if (string1 && string2 && n)
	{
		while (n)
		{
			if (*string1 != *string2)
				return (*string1 - *string2);
			if (!*string1)
				return (0);
			string1++;
			string2++;
			n--;
		}
	}
	return (0);
}
