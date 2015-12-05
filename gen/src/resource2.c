/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 21:53:41 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/05 16:47:28 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"

void			add_resource(t_inventory *inv, t_resource res)
{
	if (FOOD == res)
		inv->nb_food += 1;
	if (LINEMATE == res)
		inv->nb_linemate += 1;
	if (DERAUMERE == res)
		inv->nb_deraumere += 1;
	if (SIBUR == res)
		inv->nb_sibur += 1;
	if (MENDIANE == res)
		inv->nb_mendiane += 1;
	if (PHIRAS == res)
		inv->nb_phiras += 1;
	if (THYSTAME == res)
		inv->nb_thystame += 1;
}

int				del_resource(t_inventory *inv, t_resource res)
{
	int		have;

	have = nb_res_in_inventory(inv, res);
	if (have == 0 || have == -1)
		return (have);
	if (FOOD == res && inv->nb_food > 0)
		inv->nb_food -= 1;
	if (LINEMATE == res && inv->nb_linemate > 0)
		inv->nb_linemate -= 1;
	if (DERAUMERE == res && inv->nb_deraumere > 0)
		inv->nb_deraumere -= 1;
	if (SIBUR == res && inv->nb_sibur > 0)
		inv->nb_sibur -= 1;
	if (MENDIANE == res && inv->nb_mendiane > 0)
		inv->nb_mendiane -= 1;
	if (PHIRAS == res && inv->nb_phiras > 0)
		inv->nb_phiras -= 1;
	if (THYSTAME == res && inv->nb_thystame > 0)
		inv->nb_thystame -= 1;
	return (have);
}

int				nb_res_in_inventory(t_inventory *inv, t_resource res)
{
	if (FOOD == res)
		return (inv->nb_food);
	if (LINEMATE == res)
		return (inv->nb_linemate);
	if (DERAUMERE == res)
		return (inv->nb_deraumere);
	if (SIBUR == res)
		return (inv->nb_sibur);
	if (MENDIANE == res)
		return (inv->nb_mendiane);
	if (PHIRAS == res)
		return (inv->nb_phiras);
	if (THYSTAME == res)
		return (inv->nb_thystame);
	return (-1);
}

int				ttl_resource_in_inventory(t_inventory *inv)
{
	int		ttl;

	ttl = inv->nb_food + inv->nb_linemate + inv->nb_deraumere +
			inv->nb_sibur + inv->nb_mendiane + inv->nb_phiras +
			inv->nb_thystame;
	return (ttl);
}
