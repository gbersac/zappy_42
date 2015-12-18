/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 21:56:17 by rfrey             #+#    #+#             */
/*   Updated: 2015/12/14 19:55:39 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <sys/select.h>
	#include <sys/socket.h>
	#include "list.h"
	#include "libft.h"
}

#include "client.hpp"

void	send_buffer(t_env *env)
{
	char	*tmp;

	while (env->buf_write)
	{
		tmp = (char *)ft_listpop(&env->buf_write);
		printf("send #%s#\n", tmp);
		send(env->sock, tmp, ft_strlen(tmp), 0);
	}
}

void	read_msg(t_env *env)
{
	char	buf[BUF_SIZE + 1];
	int		r;
	int		j;
	char	**split;

	bzero(buf, BUF_SIZE + 1);
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
			// ft_putendl("play");
			play(env);
		}
		FD_SET(env->sock, &fds_read);
		//<to delete
		FD_SET(STDIN_FILENO, &fds_read);
		//to delete/>
		FD_SET(env->sock, &fds_write);
		select(env->sock + 1, &fds_read, &fds_write, NULL, NULL);
		if (env->buf_write && FD_ISSET(env->sock, &fds_write))
			send_buffer(env);
		if (FD_ISSET(env->sock, &fds_read))
		{
			// ft_putendl("read");
			read_msg(env);
		}

		// <to delete
		if (FD_ISSET(STDIN_FILENO, &fds_read))
		{
			char	buf[1];

			read(STDIN_FILENO, buf, 1);
			write(env->sock, buf, 1);
			// printf("send %s\n", buf);
		}
		// to delete/>
	}
}