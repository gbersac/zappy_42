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
//	char			*msg;
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
	send_cmd_to_client(fd, MSG_OK);
	// asprintf(&msg, "pdr %d %d", fd->trantor.id, res);
	// send_cmd_to_graphics(env, msg);
	// free(msg);
//	gfx client communication;
	int 		i;
	char		*to_send_pin;
	char		*to_send_bct;

	gfx_pdr(env, fd->trantor.id, res);
	asprintf(&to_send_pin, "pin %d\n", fd->trantor.id);
	asprintf(&to_send_bct, "bct %d %d\n", fd->trantor.pos_x, fd->trantor.pos_y);
	i = 0;
	while (i < env->maxfd)
	{
		if (env->fds[i].type == FD_GRAPHIC)
		{
			gfx_pin(env, fd, to_send_pin);
			gfx_bct(env, fd, to_send_bct);
		}
		i++;
	}
	free(to_send_pin);
	free(to_send_bct);
	return (0);
	env = NULL;
}
