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

	trantor = &(fd->trantor);
	switch (trantor->direction)
	{
		case LEFT:
			trantor->direction = UP;
			break ;
		case RIGHT:
			trantor->direction = DOWN;
			break ;
		case UP:
			trantor->direction = RIGHT;
			break ;
		case DOWN:
			trantor->direction = LEFT;
			break ;
	}
	send_cmd_to_client(fd, MSG_OK);
	env = NULL;
	cmd = NULL;
	return (0);
}
