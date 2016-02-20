/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_droite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 21:20:04 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	direction(int d)
{
	if (NORTH == d)
		return (EAST);
	if (EAST == d)
		return (SOUTH);
	if (SOUTH == d)
		return (WEST);
	if (WEST == d)
		return (NORTH);
	return (-1);
}

int			ser_droite(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;
	char			*to_send;

	trantor = &(fd->trantor);
	trantor->direction = direction(trantor->direction);
	to_send = gfx_ppo_str(trantor);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
	env = NULL;
	cmd = NULL;
	return (0);
}
