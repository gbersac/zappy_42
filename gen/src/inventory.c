/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 16:55:46 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/05 19:21:50 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"

char			*inventory_to_str(t_inventory *inv)
{
	char	*to_return;

	asprintf(&to_return, "%d %d %d %d %d %d %d",
			nb_res_in_inventory(inv, FOOD),
			nb_res_in_inventory(inv, LINEMATE),
			nb_res_in_inventory(inv, DERAUMERE),
			nb_res_in_inventory(inv, SIBUR),
			nb_res_in_inventory(inv, MENDIANE),
			nb_res_in_inventory(inv, PHIRAS),
			nb_res_in_inventory(inv, THYSTAME));
	return (to_return);
}

/*
**asprintf(&to_send, "{nourriture %d, linemate %d, deraumere %d, sibur %d, "
**		"mendiane %d, phiras %d, thystame %d}",
**		trantor->inventory.nb_food,
**		trantor->inventory.nb_linemate,
**		trantor->inventory.nb_deraumere,
**		trantor->inventory.nb_sibur,
**		trantor->inventory.nb_mendiane,
**		trantor->inventory.nb_phiras,
**		trantor->inventory.nb_thystame);
*/

t_inventory		str_to_inventory(char *str)
{
	t_inventory	to_return;

	sscanf(str, "%d %d %d %d %d %d %d",
			&to_return.nb_food,
			&to_return.nb_linemate,
			&to_return.nb_deraumere,
			&to_return.nb_sibur,
			&to_return.nb_mendiane,
			&to_return.nb_phiras,
			&to_return.nb_thystame);
	return (to_return);
}

void			sub_inventory(t_inventory *dest, t_inventory *to_sub)
{
	dest->nb_food -= to_sub->nb_food;
	dest->nb_linemate -= to_sub->nb_linemate;
	dest->nb_deraumere -= to_sub->nb_deraumere;
	dest->nb_sibur -= to_sub->nb_sibur;
	dest->nb_mendiane -= to_sub->nb_mendiane;
	dest->nb_phiras -= to_sub->nb_phiras;
	dest->nb_thystame -= to_sub->nb_thystame;
}
