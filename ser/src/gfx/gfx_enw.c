/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_enw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 17:53:45 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/06 18:27:15 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	gfx_enw(t_env *env)
{
	char	*to_send;
	t_egg	*egg;
	t_list	*iter;

	iter = env->egg;
	while (iter != NULL)
	{
		egg = (t_egg*)iter->data;
		asprintf(&to_send, "enw %d %d %d %d\n", egg->id, egg->id_trantor,
				egg->x, egg->y);
		send_cmd_to_graphics(env, to_send);
		free(to_send);
		iter = iter->next;
	}
	return (1);
}

int	gfx_enw_all(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;
	t_egg	*egg;
	t_list	*iter;

	iter = env->egg;
	while (iter != NULL)
	{
		egg = (t_egg*)iter->data;
		asprintf(&to_send, "enw %d %d %d %d\n", egg->id, egg->id_trantor,
				egg->x, egg->y);
		send_cmd_to_graphics(env, to_send);
		free(to_send);
		iter = iter->next;
	}
	return (1);
	(void)fd;
	(void)cmd;
}
