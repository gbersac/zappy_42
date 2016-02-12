/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_broadcast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 12:20:18 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/08 12:58:24 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void		send_msg_to_all_excpt_src(t_env *env, t_fd *fd, char *msg)
{
	int				i;
	char			*str;
	t_trantorian	*trant;

	i = 0;
	trant = &fd->trantor;
	while (i < env->maxfd)
	{
		if (env->fds[i].type == FD_CLIENT && env->fds[i].fd != fd->fd)
		{
			str = NULL;
			asprintf(&str, "%s %d %d %d %d %d %s",
					"message",
					trant->pos_x, trant->pos_y,
					env->fds[i].trantor.pos_x, env->fds[i].trantor.pos_y,
					env->fds[i].trantor.direction,
					msg);
			send_cmd_to_client(&env->fds[i], str);
			free(str);
		}
		i++;
	}
}

int			ser_broadcast(t_env *env, t_fd *fd, char *cmd)
{
	char	*msg;

	msg = cmd + strlen(CMD_BROADCAST) + 1;
	send_msg_to_all_excpt_src(env, fd, msg);
	gfx_pbc(env, fd, msg);
	return (0);
}
