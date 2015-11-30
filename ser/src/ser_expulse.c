/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_expulse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/11 21:03:48 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int			ser_expulse(t_env *env, t_fd *fd, char *cmd)
{
	t_square		*sq;
	t_trantorian	*trantor;
	int				i;

	trantor = &fd->trantor;
	sq = get_square(env, trantor->pos_x, trantor->pos_y);
	i = 0;
	while (i < env->maxfd)
	{
		if (env->fds[i].type == FD_CLIENT &&
				&env->fds[i] != fd &&
				env->fds[i].trantor.pos_x == trantor->pos_x &&
				env->fds[i].trantor.pos_y == trantor->pos_y)
			avance_trantor(env, &env->fds[i].trantor, trantor->direction);
		++i;
	}
	cmd = NULL;
	return (0);
}
