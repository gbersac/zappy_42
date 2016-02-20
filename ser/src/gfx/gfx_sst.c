/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_sst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 15:46:21 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 20:51:39 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int		gfx_sst(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;

	sscanf(cmd, "sst %d\n", &env->map.time_d);
	asprintf(&to_send, "sgt %d\n", env->map.time_d);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
	return (1);
	fd = NULL;
}
