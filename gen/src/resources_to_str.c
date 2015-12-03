/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 21:38:51 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/02 21:51:04 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"

static void	generate_res_str(char **prev,
								t_resource *resource,
								int have_next)
{
	char		*str_res;
	char		*buf;
	char		str[1024];

	buf = *prev;
	str_res = resource_to_str(*resource);
	if (have_next)
		sprintf(str, "%s%s ", *prev, str_res);
	else
		sprintf(str, "%s%s", *prev, str_res);
	*prev = strdup(str);
	if (buf != NULL)
		free(buf);
}

char		*resources_to_str(t_list *lst_res)
{
	char		*to_return;
	t_list		*iter;

	iter= lst_res;
	to_return = strdup("");
	while (iter != NULL)
	{
		generate_res_str(&to_return, iter->data, iter->next != NULL);
		iter = iter->next;
	}
	return (to_return);
}
