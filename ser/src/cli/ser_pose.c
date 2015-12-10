/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_pose.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/05 16:18:05 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

int			ser_pose(t_env *env, t_fd *fd, char *cmd)
{
	t_square		*sq;
	t_trantorian	*trantor;
	int				quantity_inventory;
	t_resource		res;

	sq = get_square(env, fd->trantor.pos_x, fd->trantor.pos_y);
	trantor = &fd->trantor;
	res = str_to_resource(cmd + 5);
	quantity_inventory = nb_res_in_inventory(&trantor->inventory, res);
	if (quantity_inventory < 1)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (-1);
	}
	del_resource(&trantor->inventory, res);
	add_resource(&sq->content, res);
	send_cmd_to_client(fd, MSG_OK);
	env = NULL;
	return (0);
}
