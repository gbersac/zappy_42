/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_droite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2015/11/30 19:47:21 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

int			ser_droite(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;
	int				i;
	char			*to_send;

	trantor = &(fd->trantor);
	switch (trantor->direction)
	{
		case NORTH:
			trantor->direction = EAST;
			break ;
		case EAST:
			trantor->direction = SOUTH;
			break ;
		case SOUTH:
			trantor->direction = WEST;
			break ;
		case WEST:
			trantor->direction = NORTH;
			break;
		default:
			break;
	}
	send_cmd_to_client(fd, MSG_OK);
	i = 0;
	asprintf(&to_send, "ppo %d\n", trantor->id);
	while (i < env->maxfd)
	{
		if (env->fds[i].type == FD_GRAPHIC)
			gfx_ppo(env, &env->fds[i], to_send);
		i++;
	}
	free(to_send);
	env = NULL;
	cmd = NULL;
	return (0);
}
