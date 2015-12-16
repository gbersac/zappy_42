/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:58:12 by rfrey             #+#    #+#             */
/*   Updated: 2015/12/16 16:06:54 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include "bircd.h"

void			srv_create(t_env *e, int port)
{
	int					sock;
	int					enable;
	struct sockaddr_in	sin;
	struct protoent		*pe;

	if (!((pe = (struct protoent*)getprotobyname("tcp"))))
		ft_ferror("getprotobyname error");
	if ((sock = socket(PF_INET, SOCK_STREAM, pe->p_proto)) == -1)
		ft_ferror("socket error");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	enable = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	sin.sin_port = htons(port);
	if ((bind(sock, (struct sockaddr*)&sin, sizeof(sin))) == -1)
		ft_ferror("bind error");
	if ((listen(sock, 42)) == -1)
		ft_ferror("listen error");
	e->fds[sock].type = FD_SERV;
	e->fds[sock].fct_read = srv_accept;
	e->fds[sock].to_send = NULL;
}
