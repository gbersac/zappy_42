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
	str = NULL;
	trant = &fd->trantor;
	asprintf(&str, "%s %d %s",
			"message",
			get_sound_dir(fd->trantor, *trant, env->map),
			msg);
	while (i < env->maxfd)
	{
		if (env->fds[i].type == FD_CLIENT && env->fds[i].fd != fd->fd)
			send_cmd_to_client(&env->fds[i], str);
		i++;
	}
	free(str);
}

int			ser_broadcast(t_env *env, t_fd *fd, char *cmd)
{
	char	*msg;

	msg = cmd + strlen(CMD_BROADCAST) + 1;
	send_msg_to_all_excpt_src(env, fd, msg);
	gfx_pbc(env, fd, msg);
	add_differed_msg(env, CMD_BROADCAST_TIME, fd, MSG_OK);
	return (0);
}
