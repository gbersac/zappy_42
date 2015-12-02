/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_turn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 22:22:49 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/02 18:34:33 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

static void	trantor_dead(t_env *env, int cs, t_fd *fd)
{
	ft_listpushback(&fd->to_send, strdup(MSG_DEAD));
	printf("Trantor num %d is dead\n", cs);
	close_connection(env, cs);
}

static void	decrease_life(t_env *e)
{
	int		i;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT)
		{
			--(e->fds[i].trantor.health_point);
			if (e->fds[i].trantor.health_point <= 0)
				trantor_dead(e, i, &e->fds[i]);
			if (e->fds[i].trantor.countdown > 0)
				--e->fds[i].trantor.countdown;
		}
		++i;
	}
}

static void	pop_squart_resources(t_square *sq)
{
	int		rdm;

	rdm = rand();
	if (!(rdm % POP_STONE))
		add_resources_square(sq, rdm % 6);
	if (!(rdm % POP_FOOD))
		add_resources_square(sq, FOOD);

}

static void	pop_resources(t_env *e)
{
	int		i;

	i = 0;
	while (i < e->map.width * e->map.height)
	{
		if (ft_listcnt(e->map.tartan[i].content) < MAX_RES_SQUARE)
			pop_squart_resources(&e->map.tartan[i]);
		++i;
	}
}

void		new_turn(t_env *e)
{
	decrease_life(e);
	pop_resources(e);
}
