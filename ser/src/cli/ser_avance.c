/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_avance.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/07 22:09:30 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/16 20:49:56 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

static void		move_trantor(t_env *env,
								t_trantorian	*trantor,
								t_direction dir)
{
//	printf("trantor[%d] currentpos (%d,%d)\n", trantor->id, trantor->pos_x, trantor->pos_y);
	switch (dir)
	{
		case NORTH:
			trantor->pos_y = trantor->pos_y + 1;
			break ;
		case EAST:
			trantor->pos_x = trantor->pos_x + 1;
			break ;
		case SOUTH:
			trantor->pos_y = trantor->pos_y - 1;
			break ;
		case WEST:
			trantor->pos_x = trantor->pos_x - 1;
			break ;
		default:
			break;
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
	char			*to_send;

	trantor = &fd->trantor;
	move_trantor(env, trantor, trantor->direction);
	to_send = gfx_ppo_str(trantor);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
	cmd = NULL;
	return (0);
}
