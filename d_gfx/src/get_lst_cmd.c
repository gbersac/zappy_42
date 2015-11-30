/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lst_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 20:16:25 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/11 21:31:18 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

static void		add_lst_node(t_list **lst, char *label, t_cmd_fct fct)
{
	t_cmd	*newc;

	newc = (t_cmd*)malloc(sizeof(t_cmd));
	newc->label = strdup(label);
	newc->fct = fct;
	ft_listpushback(lst, newc);
}

static void		init_lst(t_list **lst)
{
	add_lst_node(lst, "msz", gfx_msz);
	add_lst_node(lst, "bct", gfx_bct);
	add_lst_node(lst, "bct", gfx_bct);
	add_lst_node(lst, "tna", gfx_tna);
	add_lst_node(lst, "pnw", gfx_pnw);
	add_lst_node(lst, "ppo", gfx_ppo);
	add_lst_node(lst, "plv", gfx_plv);
	add_lst_node(lst, "pin", gfx_pin);
	add_lst_node(lst, "pex", gfx_pex);
	add_lst_node(lst, "pbc", gfx_pbc);
	add_lst_node(lst, "pic", gfx_pic);
	add_lst_node(lst, "pie", gfx_pie);
	add_lst_node(lst, "pfk", gfx_pfk);
	add_lst_node(lst, "pdr", gfx_pdr);
	add_lst_node(lst, "pgt", gfx_pgt);
	add_lst_node(lst, "pdi", gfx_pdi);
	add_lst_node(lst, "enw", gfx_enw);
	add_lst_node(lst, "eht", gfx_eht);
	add_lst_node(lst, "ebo", gfx_ebo);
	add_lst_node(lst, "edi", gfx_edi);
	add_lst_node(lst, "sgt", gfx_sgt);
	add_lst_node(lst, "sgt", gfx_sgt);
	add_lst_node(lst, "seg", gfx_seg);
	add_lst_node(lst, "smg", gfx_smg);
	add_lst_node(lst, "suc", gfx_suc);
	add_lst_node(lst, "sbp", gfx_sbp);
}

t_list			*get_lst_cmd(void)
{
	static t_list	*lst = NULL;

	if (lst == NULL)
	{
		init_lst(&lst);
	}
	return (lst);
}
