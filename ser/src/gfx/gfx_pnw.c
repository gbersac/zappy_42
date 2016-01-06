/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pnw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 17:59:58 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/06 18:31:43 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

char	*gfx_pnw_str(t_trantorian *trantor)
{
	char	*to_send;

	asprintf(&to_send, "pnw %d %d %d %d %d %s\n",
			trantor->id,
			trantor->pos_x,
			trantor->pos_y,
			trantor->direction,
			trantor->level,
			trantor->team);
	return (to_send);
}

void	gfx_pnw_all(t_env *e, t_fd *recipient)
{
	int				i;
	t_trantorian	*trantor;
	char			*to_send;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT)
		{
			trantor = &e->fds[i].trantor;
			to_send = gfx_pnw_str(trantor);
			send_cmd_to_client(recipient, to_send);
			free(to_send);
		}
		++i;
	}
}
