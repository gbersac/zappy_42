/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 21:56:17 by flime             #+#    #+#             */
/*   Updated: 2016/01/06 18:50:36 by gbersac          ###   ########.fr       */
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
		send(env->sock, tmp, ft_strlen(tmp), 0);
		env->n_request++;
		ft_printf("\e[0;32m[client]:\e[0m %s\n", tmp);
		// ft_printf("n_request: %d\n", env->n_request);
		if (env->buf_write != NULL)
			printf("error still to write\n");
		else
			printf("ok\n");
	}
}

/*
** Probably not good. Why not interpreting commands each after another ?
*/
void	read_msg(t_env *env)
{
	char	buf[BUF_SIZE + 1];
	int		r;
	int		j;
	char	**split;

	ft_bzero(buf, BUF_SIZE);
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
			play(env);
		FD_SET(env->sock, &fds_read);
		FD_SET(env->sock, &fds_write);
		//<to delete
		FD_SET(STDIN_FILENO, &fds_read);
		//to delete/>
		select(env->sock + 1, &fds_read, &fds_write, NULL, NULL);
		if (env->buf_write && FD_ISSET(env->sock, &fds_write))
			send_buffer(env);
		if (FD_ISSET(env->sock, &fds_read))
			read_msg(env);

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
