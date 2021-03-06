/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_prend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 21:01:14 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void		send_infos(t_env *env, t_fd *fd, t_resource res)
{
	char			*msg;

	asprintf(&msg, "pgt %d %d", fd->trantor.id, res);
	send_cmd_to_graphics(env, msg);
	free(msg);
	msg = gfx_pin_str(&fd->trantor);
	send_cmd_to_graphics(env, msg);
	free(msg);
	msg = gfx_bct_str(env, fd->trantor.pos_x, fd->trantor.pos_y);
	send_cmd_to_graphics(env, msg);
	free(msg);
}

int				ser_prend(t_env *env, t_fd *fd, char *cmd)
{
	t_square	*sq;
	int			quantity_sq;
	t_resource	res;

	sq = get_square(env, fd->trantor.pos_x, fd->trantor.pos_y);
	res = str_to_resource(cmd + 6);
	quantity_sq = nb_res_in_inventory(&sq->content, res);
	if (quantity_sq < 1)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (-1);
	}
	add_resource(&fd->trantor.inventory, res);
	del_resource(&sq->content, res);
	send_infos(env, fd, res);
	return (0);
}
