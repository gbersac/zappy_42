/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_avance.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/07 22:09:30 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/06 22:12:13 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

static void		move_trantor(t_env *env,
								t_trantorian	*trantor,
								t_direction dir)
{
	printf("avance_trantor avant x %d y %d\n", trantor->pos_x, trantor->pos_y);
	switch (dir)
	{
		case LEFT:
			trantor->pos_x = trantor->pos_x - 1;
			break ;
		case RIGHT:
			trantor->pos_x = trantor->pos_x + 1;
			break ;
		case UP:
			trantor->pos_y = trantor->pos_y - 1;
			break ;
		case DOWN:
			trantor->pos_y = trantor->pos_y + 1;
			break ;
	}
	trantor->pos_x = adjust_coord(trantor->pos_x, env->map.width);
	trantor->pos_y = adjust_coord(trantor->pos_y, env->map.height);
}

void			avance_trantor(t_env *env,
								t_trantorian	*trantor,
								t_direction dir)
{
	t_square		*sq;

	sq = get_square(env, trantor->pos_x, trantor->pos_y);
	del_resource(&sq->content, PLAYER);
	move_trantor(env, trantor, dir);
	sq = get_square(env, trantor->pos_x, trantor->pos_y);
	add_resource(&sq->content, PLAYER);
}

int				ser_avance(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;

	trantor = &fd->trantor;
	move_trantor(env, trantor, trantor->direction);
	send_cmd_to_client(fd, MSG_OK);
	cmd = NULL;
	return (0);
}
