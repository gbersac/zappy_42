/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listpushback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/05 23:24:34 by rfrey             #+#    #+#             */
/*   Updated: 2013/12/06 00:08:00 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void			ft_listpushback(t_list **list, void *data)
{
	t_list	*newn;
	t_list	*tmp;

	newn = ft_listcreate(data);
	if (list && newn)
	{
		if (*list)
		{
			tmp = *list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = newn;
		}
		else
			*list = newn;
	}
}
