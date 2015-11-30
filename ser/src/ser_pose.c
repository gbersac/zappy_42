/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_pose.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2015/11/30 20:22:19 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

int			ser_pose(t_env *env, t_fd *fd, char *cmd)
{
	t_square		*sq;
	t_trantorian	*trantor;
	int				num_node;
	t_resource		res;

	sq = get_square(env, fd->trantor.pos_x, fd->trantor.pos_y);
	trantor = &fd->trantor;
	res = str_to_resource(cmd + 5);
	num_node = has_resource(trantor->inventory, res);
	if (num_node == -1)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (-1);
	}
	ft_listpop_n(&trantor->inventory, num_node);
	add_resource(&sq->content, res);
	send_cmd_to_client(fd, MSG_OK);
	env = NULL;
	return (0);
}
