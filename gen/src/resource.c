/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 19:35:41 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/02 21:46:02 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"

static void		add_lst(t_list **lst, t_resource res, char *str)
{
	t_resource_lst	*newc;

	newc = (t_resource_lst*)malloc(sizeof(t_resource_lst));
	newc->label = strdup(str);
	newc->type = res;
	ft_listpushback(lst, newc);
}

static t_list	*init_lst(void)
{
	t_list	*lst;

	lst = NULL;
	add_lst(&lst, LINEMATE, "linemate");
	add_lst(&lst, DERAUMERE, "deraumere");
	add_lst(&lst, SIBUR, "sibur");
	add_lst(&lst, MENDIANE, "mendiane");
	add_lst(&lst, PHIRAS, "phiras");
	add_lst(&lst, THYSTAME, "thystame");
	add_lst(&lst, FOOD, "nourriture");
	add_lst(&lst, EGG, "oeuf");
	add_lst(&lst, PLAYER, "joueur");
	return (lst);
}

t_list			*get_lst_resource(void)
{
	static t_list	*lst = NULL;

	if (lst == NULL)
		lst = init_lst();
	return (lst);
}

char			*resource_to_str(t_resource res)
{
	t_list			*lst;
	t_resource_lst	*r;

	lst = get_lst_resource();
	while (lst != NULL)
	{
		r = (t_resource_lst*)lst->data;
		if (res == r->type)
			return (strdup(r->label));
		lst = lst->next;
	}
	return ("");
}

t_resource		str_to_resource(char *res)
{
	t_list			*lst;
	t_resource_lst	*r;

	lst = get_lst_resource();
	res = ft_strtrim(res);
	while (lst != NULL)
	{
		r = (t_resource_lst*)lst->data;
		if (strncmp(res, r->label, strlen(r->label)) == 0)
			return (r->type);
		lst = lst->next;
	}
	free(res);
	return (-1);
}
