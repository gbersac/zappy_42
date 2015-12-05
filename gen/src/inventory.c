/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 16:55:46 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/05 19:02:38 by gbersac          ###   ########.fr       */
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
