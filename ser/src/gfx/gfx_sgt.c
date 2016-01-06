/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_sgt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 19:34:39 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/06 18:00:14 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int		gfx_sgt(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;

	to_send = (char*)malloc(4);
	asprintf(&to_send, "sgt %d\n", env->map.time_d);
	printf("\e[0;31mto->[gfx]\e[0m %s\n", to_send);
	send_cmd_to_client(fd, to_send);
	return (1);
	cmd = NULL;
}
