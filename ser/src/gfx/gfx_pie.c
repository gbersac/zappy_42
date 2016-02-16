/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pie.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 18:14:03 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/16 21:20:30 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	gfx_pie(t_env *env, int x, int y)
{
	char	*to_send;
	t_fd	*client;
	int		i;

	asprintf(&to_send, "pie %d %d 1", x, y);
	i = 0;
	while (i < env->maxfd)
	{
		client = &env->fds[i];
		if (client->type == FD_GRAPHIC)
			add_differed_msg(env, CMD_INCANTATION_TIME, client, to_send);
		++i;
	}
	free(to_send);
	return (1);
}

