/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_fct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 23:03:03 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/05 00:02:11 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_env.h"

int		update_width(t_env *e, char **av)
{
	e->map.width = atoi(av[1]);
	if (e->map.width < 0)
	{
		fprintf(stderr, "Error: map width must be positive.\n");
		return (-1);
	}
	return (2);
}

int		update_height(t_env *e, char **av)
{
	e->map.height = atoi(av[1]);
	if (e->map.height < 0)
	{
		fprintf(stderr, "Error: map height must be positive.\n");
		return (-1);
	}
	return (2);
}

int		update_teams(t_env *e, char **av)
{
	int		i;
	char	*str;
	char	*new_str;

	i = 1;
	while (av[i] != NULL)
	{
		str = av[i];
		if (str[0] == '-')
			break ;
		new_str = strdup(str);
		ft_listpushback(&(e->map.teams), new_str);
		++i;
	}
	return (i);
}

int		update_nb(t_env *e, char **av)
{
	e->map.max_client = atoi(av[1]);
	if (e->map.max_client < 0)
	{
		fprintf(stderr, "Error: nb client must be positive.\n");
		return (-1);
	}
	return (2);
}

int		update_time(t_env *e, char **av)
{
	e->map.time_d = atoi(av[1]);
	if (e->map.time_d < 0)
	{
		fprintf(stderr, "Error: time divisor must be positive.\n");
		return (-1);
	}
	return (2);
}

