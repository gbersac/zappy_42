/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 21:12:47 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/03 15:12:21 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_env.h"

static void	usage(void)
{
	printf("Usage: ./serveur -p <port> -x <width> -y <height> -n <team>"
			" [<team>] [<team>] ... -c <nb> -t <t>\n");
	printf("\t-p numero de port\n");
	printf("\t-x largeur du Monde\n");
	printf("\t-y hauteur du Monde\n");
	printf("\t-n nom_equipe_1 nom_equipe_2 ...\n");
	printf("\t-c nombre de client autorises au commencement du jeu\n");
	printf("\t-t diviseur de l'unite de temps (plus t est grand,"
			" plus le jeu va vite)\n");
}

static int	update_port(t_env *e, char **av)
{
	char	*str;
	int		i;

	if (av[1] == NULL)
		return (-1);
	str = av[1];
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
		{
			fprintf(stderr, "Error: port must be a positive number.\n");
			return (-1);
		}
		++i;
	}
	e->port = ft_atoi(str);
	return (2);
}

static int	test_arg(t_env *e, char **av)
{
	int		i;

	i = -1;
	if (ft_strequ(av[0], "-p"))
		i = update_port(e, av);
	else if (ft_strequ(av[0], "-x"))
		i = update_width(e, av);
	else if (ft_strequ(av[0], "-y"))
		i = update_height(e, av);
	else if (ft_strequ(av[0], "-n"))
		i = update_teams(e, av);
	else if (ft_strequ(av[0], "-c"))
		i = update_nb(e, av);
	else if (ft_strequ(av[0], "-t"))
		i = update_time(e, av);
	else
		usage();
	return (i);
}

static int	test_env(t_env *e)
{
	return (e->port >= 0 &&
			e->map.width > 0 &&
			e->map.height > 0 &&
			e->map.time_d > 0 &&
			e->map.max_client > 0);
}

int			update_env(t_env *e, char **av)
{
	int		i;
	int		res;

	i = 1;
	while (av[i] != NULL)
	{
		res = test_arg(e, av + i);
		if (res == -1)
			_exit(EXIT_FAILURE);
		i += res;
	}
	if (!test_env(e))
	{
		usage();
		_exit(EXIT_FAILURE);
	}
	return (1);
}
