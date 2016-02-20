/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_msz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 14:14:15 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 20:46:50 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int		gfx_msz(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;

	asprintf(&to_send, "msz %d %d\n", env->map.width, env->map.height);
	send_cmd_to_client(fd, to_send);
	free(to_send);
	return (1);
	cmd = NULL;
}
