/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 21:53:41 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/10 20:26:17 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"

void			add_resource(t_list **lst, t_resource res)
{
	t_resource	*newc;

	newc = (t_resource*)malloc(sizeof(t_resource));
	*newc = res;
	ft_listpushback(lst, newc);
}

int				del_resource(t_list **lst, t_resource res)
{
	int		num_node;

	num_node = has_resource(*lst, res);
	if (num_node == -1)
		return (-1);
	ft_listpop_n(lst, num_node);
	return (0);
}

int				has_resource(t_list *lst_res, t_resource res)
{
	t_resource_lst	*r;
	int				i;

	i = 1;
	while (lst_res != NULL)
	{
		r = (t_resource_lst*)lst_res->data;
		if (r->type == res)
			return (i);
		lst_res = lst_res->next;
		++i;
	}
	return (-1);
}
