/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_turn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 22:22:49 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/06 22:53:27 by gbersac          ###   ########.fr       */
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
	int				i;
	t_trantorian	*trantor;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT)
		{
			trantor = &e->fds[i].trantor;
			--(trantor->health_point);
			if (trantor->health_point <= 0)
				trantor_dead(e, i, &e->fds[i]);
			if (trantor->countdown > 0){
				--trantor->countdown;
				if (trantor->countdown == 0)
					printf("trantor %d is now ready to work !\n", trantor->id);
			}
		}
		++i;
	}
}

static void	pop_squart_resources(t_square *sq)
{
	int		rdm;

	rdm = rand();
	if (!(rdm % POP_STONE))
		add_resource(&sq->content, rdm % 6 + 1);
	if (!(rdm % POP_FOOD))
		add_resource(&sq->content, FOOD);
}

static void	pop_resources(t_env *e)
{
	int		i;
	int		ttl_res;

	i = 0;
	while (i < e->map.width * e->map.height)
	{
		ttl_res = ttl_resource_in_inventory(&e->map.tartan[i].content);
		if (ttl_res < MAX_RES_SQUARE)
			pop_squart_resources(&e->map.tartan[i]);
		++i;
	}
}

void		new_turn(t_env *e)
{
	decrease_life(e);
	pop_resources(e);
}
