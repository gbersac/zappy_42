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
<<<<<<< HEAD
	char	buf[BUF_SIZE + 1];
=======
	char	*buf;
>>>>>>> bd513116d8b551ceee607b7df53a94940d50e019
	int		r;
	int		j;
	char	**split;

<<<<<<< HEAD
	bzero(buf, BUF_SIZE + 1);
=======
	buf = ft_strnew(BUF_SIZE);
>>>>>>> bd513116d8b551ceee607b7df53a94940d50e019
	r = recv(env->sock, buf, BUF_SIZE, 0);
	if (r == 0)
		ft_ferror("Disconnect by the server.");
	split = ft_strsplit(buf, '\n');
	j = 0;
	while (split[j])
<<<<<<< HEAD
	{
		// ft_putendl(split[j]);
		ft_listpushback(&env->buf_read, split[j++]);
	}
=======
		ft_listpushback(&env->buf_read, split[j++]);
>>>>>>> bd513116d8b551ceee607b7df53a94940d50e019
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
<<<<<<< HEAD
			// ft_putendl("play");
=======
			ft_putendl("play");
>>>>>>> bd513116d8b551ceee607b7df53a94940d50e019
			play(env);
		}
		FD_SET(env->sock, &fds_read);
		FD_SET(env->sock, &fds_write);
		select(env->sock + 1, &fds_read, &fds_write, NULL, NULL);
		if (env->buf_write && FD_ISSET(env->sock, &fds_write))
		{
			ft_putendl("send");
			send_buffer(env);
		}
		if (FD_ISSET(env->sock, &fds_read))
		{
<<<<<<< HEAD
			// ft_putendl("read");
			read_msg(env);
		}
		if (env->status == voir)
=======
			ft_putendl("read");
			read_msg(env);
		}

		// to delete
		if (FD_ISSET(STDIN_FILENO, &fds_read))
>>>>>>> bd513116d8b551ceee607b7df53a94940d50e019
		{
			ft_putendl("voir");
			ft_listpushback(&env->buf_write, ft_strdup("voir"));
			env->status++;
		}
		// to delete/>
	}
}
