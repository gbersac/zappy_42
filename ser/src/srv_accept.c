/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_accept.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:56:50 by rfrey             #+#    #+#             */
/*   Updated: 2015/12/06 22:44:59 by gbersac          ###   ########.fr       */
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

void		accept_player(t_env *e, int cs, char *teamname)
{
	// int					cs;
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
	e->fds[cs].trantor.team = ft_strdup(teamname);
	//	interpret_cmd(e, &e->fds[cs], "msz");
	char *nbclient= ft_strjoin(ft_itoa(e->map.max_client), "\n");
	send(cs,nbclient,strlen(nbclient),0);
	free(nbclient);
	char *width= ft_strjoin(ft_itoa(e->map.width), " ");
	char *height= ft_strjoin(ft_itoa(e->map.height), "\n");
	char *xy= ft_strjoin(width, height);
	send(cs,xy,strlen(xy),0);
	free(width);
	free(height);
	free(xy);

	char	*to_send;
	e->fds[cs].trantor.pos_x = rand() % e->map.width;
	e->fds[cs].trantor.pos_y = rand() % e->map.height;
	e->fds[cs].trantor.direction = rand() % 4;
	e->fds[cs].trantor.direction = (e->fds[cs].trantor.direction == 0) ? 4 : e->fds[cs].trantor.direction; 
	asprintf(&to_send, "pnw %d %d %d %d %d %s\n", e->fds[cs].trantor.id, e->fds[cs].trantor.pos_x, e->fds[cs].trantor.pos_y,  e->fds[cs].trantor.direction, e->fds[cs].trantor.level, e->fds[cs].trantor.team);
	printf("\e[0;31mto->[gfx]\e[0m %s\n", to_send);
	send_cmd_to_graphics(e, to_send);
}

void		accept_graphic(t_env *e, int cs)
{
	// 	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	printf("graph\n");

	csin_len = sizeof(csin);
	printf("New graphic client #%d from %s:%d\n", cs,
			inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	e->fds[cs].nickname = NULL;
	clean_fd(&e->fds[cs]);
	e->fds[cs].fd = cs;
	e->fds[cs].type = FD_GRAPHIC;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
	e->fds[cs].to_send = NULL;
//	e->fds[cs].nickname = get_dfl_nickname();
	e->fds[cs].buf_read_len = 0;
	interpret_cmd(e, &e->fds[cs], "msz");
	interpret_cmd(e, &e->fds[cs], "mct");
	interpret_cmd(e, &e->fds[cs], "tna");

	// recuperer les joueur déjà present sur le plateau

	int i;
	char	*to_send;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT)
		{
			// "pnw #n X Y O L N\n"
			asprintf(&to_send, "pnw %d %d %d %d %d %s\n", e->fds[i].trantor.id, e->fds[i].trantor.pos_x, e->fds[i].trantor.pos_y,  e->fds[i].trantor.direction, e->fds[i].trantor.level, e->fds[i].trantor.team);
			printf("\e[0;31mto->[gfx]\e[0m %s\n", to_send);
			send_cmd_to_client(&e->fds[cs], to_send);
		}
		i++;
	}

	init_trantorian(&e->fds[cs].trantor, cs);
}

void		srv_accept(t_env *e, int s)
{
	int		r;
	char	buf[BUF_SIZE + 1];
	int		cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	if ((cs = accept(s, (struct sockaddr*)&csin, &csin_len)) == -1)
		ft_ferror("accept error");
	// a mettre autre part, le serveur ne doit pas attendre reception
	char *message="BIENVENUE\n";
	send(cs,message,strlen(message),0);

	ft_bzero(buf, sizeof(buf));
	r = recv(cs, buf, BUF_SIZE, 0);
	printf("-->%s\n", buf);
	if (strncmp("GRAPHIC\n", buf, 8) == 0)
		accept_graphic(e, cs);
	else //carte??? no team name
	 	accept_player(e, cs, buf);
}
