/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 16:37:24 by rfrey             #+#    #+#             */
/*   Updated: 2014/06/05 00:01:01 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/errno.h>
#include "client.h"
#include "libft.h"
#include "general.h"

void			ft_ferror(char *msg)
{
	if (!msg)
		msg = "Undefined error";
	ft_printf("%s\n", msg);
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
			env->teamname = argv[i + 1];
		else if (ft_strequ(argv[i], "-p")&& i + 1 < argc)
			env->port = ft_atoi(argv[i + 1]);
		else if (ft_strequ(argv[i], "-h") && i + 1 < argc)
			env->hostname = argv[i + 1];
		else
			return ;
		i += 2;
	}
}

int				main(int argc, char **argv)
{
	t_env	env;

	init_env(&env);
	set_args(argc, argv, &env);
	if (!env.teamname || !env.port)
		usage(argv[0]);
	if ((env.sock = connect_to_server(env.hostname, env.port)) == -1)
		ft_ferror("Socket initialization error");
	ft_printf("Connection etablished at %s:%d\n", env.hostname, env.port);
	main_loop(&env);
	close(env.sock);
	free_env(&env);
	ft_printf("Disconnected from server.\n");
	return (EXIT_SUCCESS);
}
