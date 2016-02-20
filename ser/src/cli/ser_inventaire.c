/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_inventaire.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/08 12:53:15 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int			ser_inventaire(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;
	char			*to_send;
	char			*inventory;

	trantor = &(fd->trantor);
	inventory = inventory_to_str(&trantor->inventory);
	asprintf(&to_send, "%s %s", CMD_INVENTAIRE, inventory);
	send_cmd_to_client(fd, to_send);
	free(to_send);
	free(inventory);
	return (0);
	(void)env;
	(void)cmd;
}
