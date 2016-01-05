/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 17:56:28 by rfrey             #+#    #+#             */
/*   Updated: 2015/12/06 22:43:50 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "bircd.h"

static void	init_fd(t_env *e)
{
	int	i;

	i = 0;
	e->max = 0;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	while (i < e->maxfd)
	{
		if (e->fds[i].type != FD_FREE)
		{
			FD_SET(i, &e->fd_read);
			if (e->fds[i].to_send) {
				FD_SET(i, &e->fd_write);
			}
			e->max = MAX(e->max, i);
		}
		i++;
	}
}

static void	check_fd(t_env *e)
{
	int	i;

	i = 0;
	while (i < e->maxfd)
	{
		if (FD_ISSET(i, &e->fd_read) && e->fds[i].fct_read != NULL)
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->fd_write) && e->fds[i].fct_write != NULL)
			e->fds[i].fct_write(e, i);
		if (FD_ISSET(i, &e->fd_read) || FD_ISSET(i, &e->fd_write))
			e->r--;
		i++;
	}
}

void		main_loop(t_env *e)
{
	struct timeval	tv;

	tv.tv_sec = 0;
	tv.tv_usec = 1000;
	is_new_turn(e);
	while (42)
	{
		init_fd(e);
		e->r = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, &tv);
		check_fd(e);
		if (is_new_turn(e))
		{
			new_turn(e);
		}
	}
}
