/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_tna.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 14:14:15 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 20:43:02 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int		gfx_tna(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;
	t_list	*iter;

	printf("tna called\n");
	iter = env->map.teams;
	while (iter != NULL)
	{
		asprintf(&to_send, "tna %s\n", iter->data);
		send_cmd_to_client(fd, to_send);
		free(to_send);
		iter = iter->next;
	}
	return (1);
	cmd = NULL;
}
