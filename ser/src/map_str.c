/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 16:52:36 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/10 20:47:32 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

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

char		*square_to_str(t_env *env, int x, int y)
{
	t_square	*sq;
	char		*to_return;
	t_list		*iter;

	sq = get_square(env, x, y);
	iter= sq->content;
	to_return = strdup("");
	while (iter != NULL)
	{
		generate_res_str(&to_return, iter->data, iter->next != NULL);
		iter = iter->next;
	}
	return (to_return);
}
