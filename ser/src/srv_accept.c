/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_accept.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:56:50 by rfrey             #+#    #+#             */
/*   Updated: 2016/02/20 21:14:05 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "cmd.h"
#include "bircd.h"
#include "libft.h"

char			*get_dfl_nickname(char *teamname)
{
	static int	n = 1;
	char		*number;
	char		*nickname;

	number = ft_itoa(n);
	nickname = ft_strjoin(teamname, number);
	free(number);
	++n;
	return (nickname);
}

static void		client_write(t_env *e, int cs)
{
	char	*tmp;

	while (e->fds[cs].to_send)
	{
		tmp = (char*)ft_listpop(&e->fds[cs].to_send);
		send(cs, tmp, ft_strlen(tmp) + 1, 0);
		free(tmp);
	}
	e->fds[cs].to_send = 0;
}

void			accept_player(t_env *e, int cs, char *teamname)
{
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	printf("New client #%d from %s:%d\n", cs,
			inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	e->fds[cs].nickname = NULL;
	clean_fd(&e->fds[cs]);
	e->fds[cs].fd = cs;
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
	e->fds[cs].to_send = NULL;
	e->fds[cs].nickname = get_dfl_nickname(teamname);
	e->fds[cs].buf_read_len = 0;
	init_trantorian(&e->fds[cs].trantor, cs);
	e->fds[cs].trantor.team = ft_strdup(teamname + 11);
	e->fds[cs].trantor.pos_x = rand() % e->map.width;
	e->fds[cs].trantor.pos_y = rand() % e->map.height;
	e->fds[cs].trantor.direction = rand() % 4 + 1;
	e->fds[cs].trantor.id = cs;
	send(cs, "CONNECTED\n", strlen("CONNECTED\n"), 0);
}

void			accept_graphic(t_env *e, int cs)
{
	struct sockaddr_in	csin;

	printf("New graphic client #%d from %s:%d\n", cs,
			inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	e->fds[cs].nickname = NULL;
	clean_fd(&e->fds[cs]);
	e->fds[cs].fd = cs;
	e->fds[cs].type = FD_GRAPHIC;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
	e->fds[cs].to_send = NULL;
	e->fds[cs].buf_read_len = 0;
	interpret_cmd(e, &e->fds[cs], "msz");
	interpret_cmd(e, &e->fds[cs], "sgt");
	interpret_cmd(e, &e->fds[cs], "mct");
	interpret_cmd(e, &e->fds[cs], "tna");
	gfx_pnw_all(e, &e->fds[cs]);
	interpret_cmd(e, &e->fds[cs], "enw");
}

void			srv_accept(t_env *e, int s)
{
	int					r;
	char				buf[BUF_SIZE + 1];
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	if ((cs = accept(s, (struct sockaddr*)&csin, &csin_len)) == -1)
		ft_ferror("accept error");
	send(cs, "BIENVENUE\n", strlen("BIENVENUE\n"), 0);
	ft_bzero(buf, sizeof(buf));
	r = recv(cs, buf, BUF_SIZE, 0);
	if (strncmp("GRAPHIC\n", buf, 8) == 0)
		accept_graphic(e, cs);
	else
		accept_player(e, cs, buf);
}
