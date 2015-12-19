/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:26:04 by rfrey             #+#    #+#             */
/*   Updated: 2015/12/03 15:12:38 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "bircd.h"

/*
**static void	test_timer(t_env *e)
**{
**	int current_turn = 0;
**	int current_sec = time(NULL);
**	int	nb_turn_in_sec = 0;
**	int	nb_error = -1;
**
**	while (42)
**	{
**		if (current_sec != time(NULL))
**		{
**			printf("@@@@@@new seconde nb_error %d\n", nb_error);
**			current_sec = time(NULL);
**			if (nb_turn_in_sec != e->map.time_d)
**			{
**				printf("!!!!!!!!!!!!!!!!!!!!!Error!!!!!!!!!!!!!!!!!!!!!\n");
**				++nb_error;
**			}
**			nb_turn_in_sec = 0;
**		}
**		if (current_turn != get_num_turn(e))
**		{
**			++nb_turn_in_sec;
**			printf("new turn %d\n", nb_turn_in_sec);
**			current_turn = get_num_turn(e);
**		}
**	}
**}
*/

/* testing client main */
/*#include <netdb.h>
#include <stdio.h>
#include <errno.h>
int		main(void)
{
	int socket_desc;
	struct sockaddr_in	sin;
	struct protoent		*pe;

	if (!((pe = (struct protoent*)getprotobyname("tcp"))))
		ft_ferror("getprotobyname error");
	if ((socket_desc = socket(PF_INET, SOCK_STREAM, pe->p_proto)) == -1)
		ft_ferror("socket error");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(4242);

	// evite que le socket soit bloque apres utilisations
	int yes=1;
	if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
	    perror("setsockopt");
	    exit(1);
	}

	if ((bind(socket_desc, (struct sockaddr*)&sin, sizeof(sin))) == -1)
	{
		ft_ferror("bind error");
		printf("%s\n", strerror(errno));
	}
	if ((listen(socket_desc, 42)) == -1)
		ft_ferror("listen error");

	unsigned int addrlen;
	// struct sockaddr_in address;
	int new_socket;

  	addrlen = sizeof(sin);
  	new_socket = accept(socket_desc, (struct sockaddr *)&sin, &addrlen);
  	if (new_socket<0)
    	perror("Accept connection");

printf("bienvenue\n");
	char *message="BIENVENUE\n";
	send(new_socket,message,strlen(message),0);

    static char	buf[BUF_SIZE];
	static int	buf_len = 0;
	recv(new_socket, &buf[buf_len], BUF_SIZE - buf_len, 0);
	printf("%s", buf); //print_message

	// char *message2="YOUHOU\n";
	// send(new_socket,message2,strlen(message2),0);

	// static char	buf[BUF_SIZE];
	// static int	buf_len = 0;
	// recv(new_socket, &buf[buf_len], BUF_SIZE - buf_len, 0);
	// printf("%s", buf); //print_message

	char *nbclient="5\n";
	send(new_socket,nbclient,strlen(nbclient),0);

	char *xy="10 10\n";
	send(new_socket,xy,strlen(xy),0);

	recv(new_socket, &buf[buf_len], BUF_SIZE - buf_len, 0);
	printf("%s\n", buf); //receive broadcast

	char *ok0="ok\n";
	send(new_socket,ok0,strlen(ok0),0); //retour broadcast

	recv(new_socket, &buf[buf_len], BUF_SIZE - buf_len, 0);
	printf("%s\n", buf); //receive voir

	char *voir="{nourriture, joueur sibur, phiras phiras, }\n";
	send(new_socket,voir,strlen(voir),0);

	recv(new_socket, &buf[buf_len], BUF_SIZE - buf_len, 0);
	printf("%s\n", buf); //prend nourriture 
	char *ok="ok\n";
	send(new_socket,ok,strlen(ok),0); //ret prend

	recv(new_socket, &buf[buf_len], BUF_SIZE - buf_len, 0);
	printf("%s\n", buf); //inventaire
	char *ok2="345 3 5 10 2 1 7\n";
	send(new_socket,ok2,strlen(ok2),0); //ret inventaire

	// char *ok3="ok\n";
	// send(new_socket,ok3,strlen(ok3),0); //retour inventaire

	// recv(new_socket, &buf[buf_len], BUF_SIZE - buf_len, 0);
	// printf("%s\n", buf); //print_message

	// char *ok1="ok\n";
	// send(new_socket,ok1,strlen(ok1),0);

	// recv(new_socket, &buf[buf_len], BUF_SIZE - buf_len, 0);
	// printf("%s\n", buf); //print_message

	


	// char *ko="ko\n";
	// send(new_socket,ko,strlen(ko),0);
	while (42)
		;

	close(new_socket);

	return (0);
}*/

int			main(int ac, char **av)
{
	t_env	e;

	init_env(&e);
	update_env(&e, av);
	gen_map(&e);
	srv_create(&e, e.port);
	srand(time(NULL));
	printf("Server ready on port %d\n", e.port);

	// int i = 0;
	// while (i < e.maxfd) {
	// 	if (e.fds[i].type != FD_FREE)
	// 		printf("is free %d\n", i);
	// }

	main_loop(&e);
	return (EXIT_SUCCESS);
	ac = 0;
}

void		ft_ferror(char *msg)
{
	ft_putendl(msg);
	exit(EXIT_FAILURE);
}
