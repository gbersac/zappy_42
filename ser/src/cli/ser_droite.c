/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_droite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/08 12:22:52 by gbersac          ###   ########.fr       */
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
	add_differed_msg(env, CMD_DROITE_TIME, fd, MSG_OK);
	asprintf(&to_send, "ppo %d\n", trantor->id);
	i = 0;
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
