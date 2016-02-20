/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:53:59 by rfrey             #+#    #+#             */
/*   Updated: 2016/01/18 20:07:55 by gbersac          ###   ########.fr       */
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
	char	*to_send;

	close(cs);
	clean_fd(&e->fds[cs]);
	asprintf(&to_send, "pdi %d", cs);
	send_cmd_to_graphics(e, to_send);
	free(to_send);
	printf("client #%d gone away\n", cs);
}

static void	send_cmd(t_env *e, char *buf, int i, int cs)
{
	char	*cmd;
	int		res;

	cmd = (char*)malloc((i + 2) * sizeof(char));
	memcpy(cmd, buf, i + 1);
	cmd[i + 1] = '\0';
	res = interpret_cmd(e, &e->fds[cs], cmd);
	free(cmd);
	if (res == 1)
		close_connection(e, cs);
	else
	{
		memcpy(buf, buf + i + 1, strlen(buf) - i);
		e->fds[cs].buf_read_len = strlen(buf);
		buf[e->fds[cs].buf_read_len] = '\0';
	}
}

void		extract_cmd_from_buffer(t_env *e, int cs)
{
	int		i;
	char	*buf;

	buf = e->fds[cs].buf_read;
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			send_cmd(e, buf, i, cs);
			i = 0;
		}
		else
			++i;
	}
}

void		client_read(t_env *e, int cs)
{
	int		r;
	char	buf[BUF_SIZE + 1];

	r = recv(cs, buf, BUF_SIZE, 0);
	buf[r] = '\0';
	// printf("<-[%d]-- %s\n", cs, buf);
	if (r <= 0)
		close_connection(e, cs);
	else
	{
		ft_memcpy(&(e->fds[cs].buf_read[e->fds[cs].buf_read_len]), buf, r + 1);
		e->fds[cs].buf_read_len += r;
		extract_cmd_from_buffer(e, cs);
	}
}
