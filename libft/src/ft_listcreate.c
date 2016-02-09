/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listcreate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/05 23:18:33 by rfrey             #+#    #+#             */
/*   Updated: 2014/02/06 23:58:52 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

t_list			*ft_listcreate(void *data)
{
	t_list	*newn;

	newn = NULL;
	newn = (t_list *)malloc(sizeof(*newn));
	if (newn != NULL)
	{
		newn->data = data;
		newn->next = NULL;
	}
	return (newn);
}
