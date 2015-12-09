/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incantation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 21:37:20 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/06 21:37:51 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incantation.h"

static void		add_node(t_incantation *incant, char *str)
{
	incant->big_level = str[0] - '0';
	incant->end_level = str[0] + 1 - '0';
	incant->players = str[1] - '0';
	incant->required_resources = str_to_inventory(str + 3);
}

t_incantation	*get_lst_lvl(void)
{
	static t_incantation	*incants = NULL;

	if (incants == NULL)
	{
		incants = (t_incantation*)malloc(sizeof(t_incantation) * (NB_LEVEL));
		add_node(incants + 0, "11 0 1 0 0 0 0 0");
		add_node(incants + 1, "22 0 1 1 1 0 0 0");
		add_node(incants + 2, "32 0 2 0 1 0 2 0");
		add_node(incants + 3, "44 0 1 1 2 0 1 0");
		add_node(incants + 4, "54 0 1 2 1 3 0 0");
		add_node(incants + 5, "66 0 1 2 3 0 1 0");
		add_node(incants + 6, "76 0 2 2 2 2 2 1");
	}
	return (incants);
}

t_incantation	incantation_to_evolve(int level)
{
	return (get_lst_lvl()[level - 1]);
}
