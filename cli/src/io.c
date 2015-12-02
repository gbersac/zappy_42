/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 21:56:17 by rfrey             #+#    #+#             */
/*   Updated: 2014/06/10 16:40:32 by gbersac          ###   ########.fr       */
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

	while (env->buf_write)
	{
		tmp = (char *)ft_listpop(&env->buf_write);
		send(env->sock, tmp, ft_strlen(tmp) + 1, 0);
	}
}

void	read_msg(t_env *env)
{
	static char	buf[BUF_SIZE];
	static int	buf_len = 0;
	int			r;
	int			i;
	int			l;

	r = recv(env->sock, &buf[buf_len], BUF_SIZE - buf_len, 0);
	if (r == 0)
		ft_ferror("Disconnect by the server.");
	i = buf_len;
	buf_len += r;
	while (i < buf_len)
	{
		if (!buf[i])
		{
			if ((l = ft_strlen(buf)))
				ft_listpushback(&env->buf_read, ft_strsub(buf, 0, l));
			ft_memcpy(buf, &buf[i + 1], buf_len - i - 1);
			buf_len = buf_len - i - 1;
		}
		++i;
	}
	printf("%s\n", buf);
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
		//to delete
		FD_SET(0, &fds_read);
		//to delete
		FD_SET(env->sock, &fds_write);
		select(env->sock + 1, &fds_read, &fds_write, NULL, NULL);
		if (env->buf_write && FD_ISSET(env->sock, &fds_write))
			send_buffer(env);
		if (FD_ISSET(env->sock, &fds_read))
			read_msg(env);

		// to delete
		if (FD_ISSET(0, &fds_read))
		{
			char	buf[1];

			read(STDIN_FILENO, buf, 1);
			write(env->sock, buf, 1);
			// printf("send %s\n", buf);
		}
		// to delete
	}
}