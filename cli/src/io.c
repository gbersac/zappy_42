/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 21:56:17 by flime             #+#    #+#             */
/*   Updated: 2015/12/24 20:22:46 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include "list.h"
#include "libft.h"
#include "client.h"

void	send_buffer(t_env *env)
{
	char	*tmp;

	while (env->buf_write && env->n_request < 10)
	{
		tmp = (char *)ft_listpop(&env->buf_write);
		ft_listpushback(&env->buf_pending, tmp);
		send(env->sock, tmp, ft_strlen(tmp) + 1, 0);
		env->n_request++;
		ft_printf("send: %s\n", tmp);
		ft_printf("n_request: %d\n", env->n_request);
	}
}

void	read_msg(t_env *env)
{
	char	*buf;
	int		r;
	int		j;
	char	**split;

	buf = ft_strnew(BUF_SIZE);
	r = recv(env->sock, buf, BUF_SIZE, 0);
	if (r == 0)
		ft_ferror("Disconnect by the server.");
	split = ft_strsplit(buf, '\n');
	j = 0;
	while (split[j])
		ft_listpushback(&env->buf_read, split[j++]);
	//a faire
	//free(split[]) et sous split;
}

void	main_loop(t_env *env)
{
	fd_set	fds_read;
	fd_set	fds_write;

	FD_ZERO(&fds_read);
	FD_ZERO(&fds_write);
	while (42)
	{
		if (env->buf_read)
		{
			ft_putendl("play");
			play(env);
		}
		FD_SET(env->sock, &fds_read);
		FD_SET(env->sock, &fds_write);
		select(env->sock + 1, &fds_read, &fds_write, NULL, NULL);
		if (env->buf_write && FD_ISSET(env->sock, &fds_write))
			send_buffer(env);
		if (FD_ISSET(env->sock, &fds_read))
			read_msg(env);
		ft_putendl("loop");
		sleep(1);
		// if (env->status == voir)
		// {
		// 	ft_putendl("voir");
		// 	ft_listpushback(&env->buf_write, ft_strdup("voir"));
		// 	env->status++;
		// }
		// to delete/>
	}
}
