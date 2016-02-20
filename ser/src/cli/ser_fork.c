/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 19:11:58 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 21:02:29 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int			ser_fork(t_env *env, t_fd *fd, char *cmd)
{
	t_egg	*new_egg;
	char	*msg;

	cmd = NULL;
	new_egg = (t_egg*)malloc(sizeof(t_egg));
	new_egg->countdown = -1;
	printf("ser_fork team %s at %d %d\n", fd->trantor.team,
			fd->trantor.pos_x,
			fd->trantor.pos_y);
	new_egg->team = fd->trantor.team;
	new_egg->x = fd->trantor.pos_x;
	new_egg->y = fd->trantor.pos_y;
	new_egg->id_trantor = fd->fd;
	fd->trantor.laying = 1;
	ft_listpushback(&env->egg, new_egg);
	asprintf(&msg, "pfk %d", fd->trantor.id);
	send_cmd_to_graphics(env, msg);
	free(msg);
	return (0);
}
