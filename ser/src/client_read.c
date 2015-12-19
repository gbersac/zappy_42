/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:53:59 by rfrey             #+#    #+#             */
/*   Updated: 2015/12/14 19:56:32 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	send_to_others(t_env *e, int cs)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(e->fds[cs].nickname, " says : ");
	tmp2 = ft_strjoin(tmp, e->fds[cs].buf_read);
	i = 0;
	while (i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT)
			&& (i != cs))
		{
			ft_listpushback(&e->fds[i].to_send, ft_strdup(tmp2));
		}
		i++;
	}
	free(tmp);
	free(tmp2);
}

void	close_connection(t_env *e, int cs)
{
	close(cs);
	clean_fd(&e->fds[cs]);
	printf("client #%d gone away\n", cs);
}

void	client_read(t_env *e, int cs)
{
	int		r;
	char	buf[BUF_SIZE + 1];
	int		res;

	r = recv(cs, buf, BUF_SIZE, 0);
	printf("--[read]> %s\n", buf);
	if (r <= 0)
		close_connection(e, cs);
	else
	{
		ft_memcpy(&(e->fds[cs].buf_read[e->fds[cs].buf_read_len]), buf, r);
		e->fds[cs].buf_read_len += r;
		if (e->fds[cs].buf_read[e->fds[cs].buf_read_len - 1] == '\n')
		{
			res = interpret_cmd(e, &e->fds[cs], e->fds[cs].buf_read);
			if (res == 1)
				close_connection(e, cs);
			else
			{
				bzero(e->fds[cs].buf_read, BUF_SIZE);
				e->fds[cs].buf_read_len = 0;
			}
		}
	}
}
