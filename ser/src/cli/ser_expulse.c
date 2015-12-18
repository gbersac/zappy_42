/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_expulse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/18 17:09:58 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void	expulse_one_fd(t_env *env, t_fd *target, t_fd *expulsor)
{
	t_trantorian	*trantor;
	char			*to_send;

	trantor = &expulsor->trantor;
	if (target->type == FD_CLIENT &&
			expulsor != target &&
			target->trantor.pos_x == trantor->pos_x &&
			target->trantor.pos_y == trantor->pos_y)
	{
		avance_trantor(env, &target->trantor, trantor->direction);
		asprintf(&to_send, "deplacement %d\n",
				direction_to_nbr(trantor->direction));
		send_cmd_to_client(target, to_send);
	}
}

int			ser_expulse(t_env *env, t_fd *fd, char *cmd)
{
	int		i;

	i = 0;
	if (fd->type != FD_CLIENT)
	{
		printf("ser_expulse forbiden client.\n");
		return (-1);
	}
	while (i < env->maxfd)
	{
		expulse_one_fd(env, &env->fds[i], fd);
		++i;
	}
	gfx_pex(env, fd);
	cmd = NULL;
	return (0);
}
