/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 19:34:39 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/08 12:39:29 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static char	*trantors_id_to_str(t_list *trantors)
{
	char			*to_return;
	char			*buf;
	t_trantorian	*trantor;

	to_return = strdup("");
	while (trantors != NULL)
	{
		trantor = (t_trantorian*) trantors->data;
		buf = to_return;
		asprintf(&to_return, "%s %d ", to_return, trantor->id);
		free(buf);
		trantors = trantors->next;
	}
	return (to_return);
}

int			gfx_pic(t_env *env, t_list *fds)
{
	char			*to_send;
	char			*ids;
	t_trantorian	*first;

	if (fds == NULL)
		printf("ERROR: gfx_pic fds is NULL\n");
	first = (t_trantorian*) fds->data;
	ids = trantors_id_to_str(fds);
	asprintf(&to_send, "pic %d %d %d %s\n",
			first->pos_x,
			first->pos_y,
			first->level,
			ids);
	printf("ids #%s#\n", ids);
	free(ids);
	send_cmd_to_graphics(env, to_send);
	return (1);
}
