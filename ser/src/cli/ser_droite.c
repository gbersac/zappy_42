/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_droite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/16 20:53:14 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

int			ser_droite(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;
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
	to_send = gfx_ppo_str(trantor);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
	env = NULL;
	cmd = NULL;
	return (0);
}
