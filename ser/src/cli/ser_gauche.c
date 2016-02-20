/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_gauche.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 14:14:15 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 21:27:09 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	direction(int d)
{
	if (NORTH == d)
		return (WEST);
	if (EAST == d)
		return (NORTH);
	if (SOUTH == d)
		return (EAST);
	if (WEST == d)
		return (SOUTH);
	return (-1);
}

int			ser_gauche(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;
	char			*to_send;

	trantor = &(fd->trantor);
	trantor->direction = direction(trantor->direction);
	to_send = gfx_ppo_str(trantor);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
	return (0);
	(void)env;
	(void)cmd;
}
