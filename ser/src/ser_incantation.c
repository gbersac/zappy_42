/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_incantation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/11 21:02:09 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

static t_list	*get_lst_trantor(t_env *env, int level, int x, int y)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = NULL;
	while (i < env->maxfd)
	{
		if (env->fds[i].type == FD_CLIENT &&
				env->fds[i].trantor.pos_x == x &&
				env->fds[i].trantor.pos_y == y &&
				env->fds[i].trantor.level == level)
			ft_listpushback(&lst, &env->fds[i]);
		++i;
	}
	return (lst);
}

int				ser_incantation(t_env *env, t_fd *fd, char *cmd)
{
	t_square		*sq;
	t_trantorian	*trantor;
	t_list			*lst;

	trantor = &fd->trantor;
	sq = get_square(env, trantor->pos_x, trantor->pos_y);
	lst = get_lst_trantor(env, trantor->level, trantor->pos_x, trantor->pos_y);
	cmd = NULL;
	return (0);
}
