/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_prend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/08 12:54:19 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

int				ser_prend(t_env *env, t_fd *fd, char *cmd)
{
	char		*msg;
	t_square	*sq;
	int			quantity_sq;
	t_resource	res;

	sq = get_square(env, fd->trantor.pos_x, fd->trantor.pos_y);
	res = atoi(cmd + 6);
	quantity_sq = nb_res_in_inventory(&sq->content, res);
	if (quantity_sq < 1)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (-1);
	}
	add_resource(&fd->trantor.inventory, res);
	del_resource(&sq->content, res);
	add_differed_msg(env, CMD_PREND_TIME, fd, MSG_OK);
	asprintf(&msg, "bct %d %d\n", fd->trantor.pos_x, fd->trantor.pos_y);
	send_cmd_to_graphics(env, msg);
	return (0);
}
