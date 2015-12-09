/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 14:26:30 by flime             #+#    #+#             */
/*   Updated: 2015/10/28 23:52:45 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Search if a string is a valid number (string is should be trimmed first)
*/

int	ft_strisdigit(char *str)
{
	int	i;

	i = (str[0] == '-' || str[0] == '+') ? 1 : 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
