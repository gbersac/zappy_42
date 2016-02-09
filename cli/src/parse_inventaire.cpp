/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inventaire.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 23:16:41 by flime             #+#    #+#             */
/*   Updated: 2015/12/24 00:23:07 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include "client.hpp"

/*
** Takes a string of the inventory in the form :
** %d         %d       %d       %d    %d       %d     %d
** nourriture linemate deraumes sibur mendiane phiras thystame
**
** and fill the inventory
*/

void	parse_inventaire(t_env *env, char *str)
{
	char	**astr;

	astr = ft_strsplit(str, ' ');
	env->inventory.nb_food = ft_atoi(astr[1]);
	env->inventory.nb_linemate = ft_atoi(astr[2]);
	env->inventory.nb_deraumere = ft_atoi(astr[3]);
	env->inventory.nb_sibur = ft_atoi(astr[4]);
	env->inventory.nb_mendiane = ft_atoi(astr[5]);
	env->inventory.nb_phiras = ft_atoi(astr[6]);
	env->inventory.nb_thystame = ft_atoi(astr[7]);
	print_inventaire(env);
}
