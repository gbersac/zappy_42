/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:55:31 by rfrey             #+#    #+#             */
/*   Updated: 2014/06/04 22:40:47 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/resource.h>
#include "bircd.h"

void		init_map(t_map *map)
{
	map->width = -1;
	map->height = -1;
	map->teams = NULL;
	map->time_d = -1;
	map->max_client = -1;
}

void		init_env(t_env *e)
{
	int				i;
	struct rlimit	rlp;
	int				ret;

	bzero(e, sizeof(t_env));
	if ((ret = getrlimit(RLIMIT_NOFILE, &rlp)) == -1)
		ft_ferror("getrlimit error");
	e->maxfd = rlp.rlim_cur;
	if (!((e->fds = (t_fd*)malloc(sizeof(*e->fds) * e->maxfd))))
		ft_ferror("malloc error");
	i = 0;
	while (i < e->maxfd)
	{
		clean_fd(&e->fds[i]);
		i++;
	}
	e->port = -1;
	init_map(&(e->map));
}
