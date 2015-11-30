/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_prend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/11 21:07:07 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

int				ser_prend(t_env *env, t_fd *fd, char *cmd)
{
	t_square	*sq;
	int			num_node;
	t_resource	res;

	sq = get_square(env, fd->trantor.pos_x, fd->trantor.pos_y);
	res = str_to_resource(cmd + 6);
	num_node = has_resource(sq->content, res);
	if (num_node == -1)
	{
		ft_listpushback(&fd->to_send, strdup(MSG_KO));
		return (-1);
	}
	ft_listpop_n(&sq->content, num_node);
	if (res == FOOD)
		fd->trantor.health_point += LIFE_LONG;
	else
		add_resource(&fd->trantor.inventory, res);
	ft_listpushback(&fd->to_send, strdup(MSG_OK));
	env = NULL;
	return (0);
}
