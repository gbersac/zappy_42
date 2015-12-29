/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_sst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 15:46:21 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/19 19:18:39 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int     gfx_sst(t_env *env, t_fd *fd, char *cmd)
{
<<<<<<< HEAD
    char    *to_send;
=======

	printf("sst called\n");
	return (1);
	env = NULL;
	cmd = NULL;
	fd = NULL;
}
>>>>>>> bd513116d8b551ceee607b7df53a94940d50e019

    sscanf(cmd, "sst %d\n", &env->map.time_d);
    asprintf(&to_send, "sgt %d\n", env->map.time_d);
    send_cmd_to_graphics(env, to_send);
    free(to_send);
    return (1);
    fd = NULL;
}
