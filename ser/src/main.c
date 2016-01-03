/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:26:04 by rfrey             #+#    #+#             */
/*   Updated: 2015/12/24 17:57:01 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "bircd.h"

int			main(int ac, char **av)
{
	t_env	e;

	init_env(&e);
	update_env(&e, av);
	gen_map(&e);
	srv_create(&e, e.port);
	srand(time(NULL));
	printf("Server ready on port %d\n", e.port);
	main_loop(&e);
	return (EXIT_SUCCESS);
	ac = 0;
}

void		ft_ferror(char *msg)
{
	ft_putendl(msg);
	exit(EXIT_FAILURE);
}
