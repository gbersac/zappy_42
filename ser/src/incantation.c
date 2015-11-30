/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incantation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 21:37:20 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/11 21:02:24 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incantation.h"

static void		add_node(t_incantation *incant, char *str)
{
	incant->beg_level = str[0];
	incant->end_level = str[0] + 1;
	incant->players = str[1];
	incant->nb_linemate = str[2];
	incant->nb_deraumere = str[3];
	incant->nb_sibur = str[4];
	incant->nb_mendiane = str[5];
	incant->nb_phiras = str[6];
	incant->nb_thystame = str[7];
}

t_incantation	*get_lst_lvl(void)
{
	static t_incantation	*incants = NULL;

	if (incants == NULL)
	{
		incants = (t_incantation*)malloc(sizeof(t_incantation) * (NB_LEVEL));
		add_node(incants + 0, "11100000");
		add_node(incants + 1, "22111000");
		add_node(incants + 2, "32201020");
		add_node(incants + 3, "44112010");
		add_node(incants + 4, "54121300");
		add_node(incants + 5, "66123010");
		add_node(incants + 6, "76222221");
	}
	return (incants);
}
