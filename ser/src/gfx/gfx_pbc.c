/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 14:14:15 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 20:51:52 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	gfx_pbc(t_env *env, t_fd *fd, char *msg)
{
	char	*to_send;

	asprintf(&to_send, "pbc %d %s",
			fd->trantor.id,
			msg);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
	return (1);
}
