/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_ppo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 20:38:26 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/16 20:50:13 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

char	*gfx_ppo_str(t_trantorian *trantor)
{
	char			*to_send;

	asprintf(&to_send, "ppo %d %d %d %d",
			trantor->id,
			trantor->pos_x,
			trantor->pos_y,
			direction_to_nbr(trantor->direction));
	return (to_send);
}

int		gfx_ppo(t_env *env, t_fd *fd, char *cmd)
{
	char			*to_send;
	int				num;
	int				res;
	t_trantorian	*trantor;

	res = sscanf(cmd, "ppo %d\n", &num);
	printf("called %s\n", cmd);
	if (res < 1 || env->fds[num].type != FD_CLIENT)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (0);
	}
	trantor = &env->fds[num].trantor;
	to_send = gfx_ppo_str(trantor);
	send_cmd_to_client(fd, to_send);
	free(to_send);
	return (1);
}
