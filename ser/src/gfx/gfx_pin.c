/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 14:15:54 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/05 17:02:27 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int			gfx_pin(t_env *env, t_fd *fd, char *cmd)
{
	char			*to_send;
	int				num;
	t_trantorian	*trantor;
	char			*inv_str;

	sscanf(cmd, "pin %d\n", &num);
	trantor = &env->fds[num].trantor;
	if (env->fds[num].type != FD_CLIENT)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (0);
	}
	inv_str = inventory_to_str(&trantor->inventory);
	asprintf(&to_send, "pin %d %d %d %s",
			num,
			trantor->pos_x,
			trantor->pos_y,
			inv_str);
	printf("\e[0;31mto->[gfx]\e[0m %s\n", to_send);
	send_cmd_to_client(fd, to_send);
	free(inv_str);
	free(to_send);
	return (1);
}
