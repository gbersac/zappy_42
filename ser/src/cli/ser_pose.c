/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_pose.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <mdebelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/08 16:19:20 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void	send_infos(t_env *env, t_fd *fd, t_resource res)
{
	char			*msg;

	asprintf(&msg, "pdr %d %d", fd->trantor.id, res);
	send_cmd_to_graphics(env, msg);
	free(msg);
	msg = gfx_pin_str(&fd->trantor);
	send_cmd_to_graphics(env, msg);
	free(msg);
	msg = gfx_bct_str(env, fd->trantor.pos_x, fd->trantor.pos_y);
	send_cmd_to_graphics(env, msg);
	free(msg);
}

int			ser_pose(t_env *env, t_fd *fd, char *cmd)
{
	t_square		*sq;
	t_trantorian	*trantor;
	int				quantity_inventory;
	t_resource		res;

	sq = get_square(env, fd->trantor.pos_x, fd->trantor.pos_y);
	trantor = &fd->trantor;
	res = atoi(cmd + 5);
	quantity_inventory = nb_res_in_inventory(&trantor->inventory, res);
	if (quantity_inventory < 1)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (-1);
	}
	del_resource(&trantor->inventory, res);
	add_resource(&sq->content, res);
	send_infos(env, fd, res);
	return (0);
}
