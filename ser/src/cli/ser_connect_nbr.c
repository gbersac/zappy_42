/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_connect_nbr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 14:14:15 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 21:01:34 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int					ser_connect_nbr(t_env *env, t_fd *fd, char *cmd)
{
	char	*msg;

	asprintf(&msg, "%s %d", CMD_CONNECT_NBR,
			available_connexion(env, fd->trantor.team));
	send_cmd_to_client(fd, msg);
	return (0);
	(void)cmd;
}
