/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_accept.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:56:50 by rfrey             #+#    #+#             */
/*   Updated: 2015/12/02 19:42:49 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "bircd.h"
#include "libft.h"

char			*get_dfl_nickname(void)
{
	static int	n = 1;
	char		*number;
	char		*nickname;

	number = ft_itoa(n);
	nickname = ft_strjoin("Timmy", number);
	free(number);
	++n;
	return (nickname);
}

/*
** Each message to send must be allocated on the heap.
*/
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

void		accept_player(t_env *e, int s)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	if ((cs = accept(s, (struct sockaddr*)&csin, &csin_len)) == -1)
		ft_ferror("accept error");
	printf("New client #%d from %s:%d\n", cs,
			inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	e->fds[cs].nickname = NULL;
	clean_fd(&e->fds[cs]);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
	e->fds[cs].to_send = NULL;
	e->fds[cs].nickname = get_dfl_nickname();
	e->fds[cs].buf_read_len = 0;
	init_trantorian(&e->fds[cs].trantor);
}

void		accept_graphic(t_env *e, int s)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	if ((cs = accept(s, (struct sockaddr*)&csin, &csin_len)) == -1)
		ft_ferror("accept error");
	printf("New graphic client #%d from %s:%d\n", cs,
			inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	e->fds[cs].nickname = NULL;
	clean_fd(&e->fds[cs]);
	e->fds[cs].fd = cs;
	e->fds[cs].type = FD_GRAPHIC;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
	e->fds[cs].to_send = NULL;
	e->fds[cs].nickname = get_dfl_nickname();
	e->fds[cs].buf_read_len = 0;
	init_trantorian(&e->fds[cs].trantor);
}

void srv_accept(t_env *e, int cs)
{
	int		r;
	char	buf[BUF_SIZE + 1];

	r = recv(cs, buf, BUF_SIZE, 0);
	if (strncmp("GRAPHIC\n", buf, 8))
		accept_graphic(e, cs);
	else
		accept_player(e, cs);
}
