/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_prend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/06 22:49:02 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

int				ser_prend(t_env *env, t_fd *fd, char *cmd)
{
	t_square	*sq;
	char		*msg;
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
	if (res == FOOD)
		fd->trantor.health_point += LIFE_LONG;
	else
		add_resource(&fd->trantor.inventory, res);
	del_resource(&sq->content, res);
	send_cmd_to_client(fd, MSG_OK);
	asprintf(&msg, "pgt %d %d", fd->trantor.id, res);
	send_cmd_to_graphics(env, msg);
	free(msg);
	return (0);
	env = NULL;
}
