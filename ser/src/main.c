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
