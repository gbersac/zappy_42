/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 14:15:54 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/06 19:18:13 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

char		*gfx_pin_str(t_trantorian *trantor)
{
	char	*to_send;
	char	*inv_str;

	inv_str = inventory_to_str(&trantor->inventory);
	asprintf(&to_send, "pin %d %d %d %s",
			trantor->id,
			trantor->pos_x,
			trantor->pos_y,
			inv_str);
	free(inv_str);
	return (to_send);
}

int			gfx_pin(t_env *env, t_fd *fd, char *cmd)
{
	char			*to_send;
	int				num;
	t_trantorian	*trantor;

	sscanf(cmd, "pin %d\n", &num);
	trantor = &env->fds[num].trantor;
	if (env->fds[num].type != FD_CLIENT)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (0);
	}
	to_send = gfx_pin_str(trantor);
	send_cmd_to_client(fd, to_send);
	free(to_send);
	return (1);
}
