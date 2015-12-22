/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:18:14 by flime             #+#    #+#             */
/*   Updated: 2015/11/30 17:18:23 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <stdlib.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <sys/errno.h>

	#include "libft.h"
	#include "general.h"
}

#include "client.hpp"

void			ft_ferror(std::string msg)
{
	if (msg == "")
		std::cout << "Undefined error" << std::endl;
	ft_printf("%s\n", msg.c_str());
	if (errno)
		perror(NULL);
	exit(EXIT_FAILURE);
}

static void		usage(char *progname)
{
	ft_printf("usage : %s -n <team> -p <port> [-h <hostname>]\n", progname);
	exit(EXIT_FAILURE);
}

static void		set_args(int argc, char **argv, t_env *env)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-n") && i + 1 < argc)
			env->trantor.team = argv[i + 1];
		else if (ft_strequ(argv[i], "-p")&& i + 1 < argc)
			env->port = ft_atoi(argv[i + 1]);
		else if (ft_strequ(argv[i], "-h") && i + 1 < argc)
			env->hostname = argv[i + 1];
		else
			return ;
		i += 2;
	}
}

// int				main(int argc, char **argv)
// {
// 	t_env	env;

// 	init_env(&env);
// 	env.status = init;
// 	set_args(argc, argv, &env);
// 	env.n_request = 0;
// 	env.role = valet;
// 	if (!env.teamname || !env.port)
// 		usage(argv[0]);
// 	if ((env.sock = connect_to_server(env.hostname, env.port)) == -1)
// 		ft_ferror("Socket initialization error");
// 	env.n_request++;
// 	ft_printf("Connection etablished at %s:%d\n", env.hostname, env.port);
// 	//printf("%s\n", env.teamname);
// 	main_loop(&env);
// 	close(env.sock);
// 	free_env(&env);
// 	ft_printf("Disconnected from server.\n");
// 	return (EXIT_SUCCESS);
// }

/* client test main */
#include <netdb.h>
int				main(int argc, char **argv)
{
	t_env	env;

	init_env(&env);
	set_args(argc, argv, &env);
	if (!env.trantor.team || !env.port)
		usage(argv[0]);
	if ((env.sock = connect_to_server(env.hostname, env.port)) == -1)
		ft_ferror("Socket initialization error");
	ft_printf("Connection etablished at %s:%d\n", env.hostname, env.port);
	// printf("%s\n", env.teamname);

	static char	buf[BUF_SIZE];
	static int	buf_len = 0;
	recv(env.sock, &buf[buf_len], BUF_SIZE - buf_len, 0);
	printf("%s", buf); //print_message

	//char *team= "one\n";
	//send(env.sock,team,strlen(team),0);

	ft_strclr(buf);
	buf_len = 0;
	recv(env.sock, &buf[buf_len], BUF_SIZE - buf_len, 0);
	printf("%s", buf); //print_message

	ft_strclr(buf);
	buf_len = 0;
	recv(env.sock, &buf[buf_len], BUF_SIZE - buf_len, 0);
	printf("%s", buf); //print_message

	// main_loop(&env);
	close(env.sock);
	free_env(&env);
	ft_printf("Disconnected from server.\n");
	return (EXIT_SUCCESS);
}
