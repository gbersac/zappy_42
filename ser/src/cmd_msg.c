/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/22 17:11:27 by rfrey             #+#    #+#             */
/*   Updated: 2016/01/08 12:57:37 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "bircd.h"

void	send_cmd_to_client(t_fd *fd, char *str)
{
	char *to_send;

	to_send = ft_strjoin(str, "\n");
	ft_listpushback(&fd->to_send, to_send);
}

void	send_cmd_to_graphics(t_env *env, char *str)
{
	char	*to_send;
	int		i;
	t_fd	*client;

	printf("\e[0;31mto->[gfx]\e[0m %s\n", str);
	to_send = ft_strjoin(str, "\n");
	i = 0;
	while (i < env->maxfd)
	{
		client = &env->fds[i];
		if (client->type == FD_GRAPHIC)
			ft_listpushback(&client->to_send, to_send);
		++i;
	}
}

void	send_cmd_to_clients(t_env *env, char *str)
{
	char	*to_send;
	int		i;
	t_fd	*client;

	to_send = ft_strjoin(str, "\n");
	i = 0;
	while (i < env->maxfd)
	{
		client = &env->fds[i];
		if (client->type == FD_CLIENT)
			ft_listpushback(&client->to_send, to_send);
		++i;
	}
}

void	send_cmd_to_all(t_env *env, char *str)
{
	char	*to_send;
	int		i;
	t_fd	*client;

	to_send = ft_strjoin(str, "\n");
	i = 0;
	while (i < env->maxfd)
	{
		client = &env->fds[i];
		if (client->type == FD_GRAPHIC || client->type == FD_CLIENT)
			ft_listpushback(&client->to_send, to_send);
		++i;
	}
}

void	add_differed_msg(t_env *env, int countdown, t_fd *recipient, char *msg)
{
	t_differed_msg	*dmsg;

	dmsg = (t_differed_msg*)malloc(sizeof(t_differed_msg));
	dmsg->countdown = countdown;
	dmsg->recipient = recipient;
	dmsg->msg = strdup(msg);
	ft_listpushback(&env->differed_msg, dmsg);
}
