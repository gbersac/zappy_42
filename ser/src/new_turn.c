/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_turn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 22:22:49 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 21:25:19 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void		decrease_life(t_env *e)
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
			if (trantor->health_point == 0)
			{
				if (trantor->inventory.nb_food > 1)
				{
					--trantor->inventory.nb_food;
					trantor->health_point += LIFE_LONG * INIT_LIFE;
				}
				else
					trantor_dead(e, i, &e->fds[i]);
			}
		}
		++i;
	}
}

static void		pop_squar_resources(t_env *env, t_square *sq, int ttl_res)
{
	int		rdm;
	int		change;
	int		res;
	char	*to_send;

	rdm = rand();
	change = 0;
	if (!(rdm % POP_STONE) && (ttl_res - sq->content.nb_food) < MAX_RES_SQUARE)
	{
		change = 1;
		res = rdm % 7 + 1;
		add_resource(&sq->content, res);
	}
	if (!(rdm % POP_FOOD) && sq->content.nb_food == 0)
	{
		change = 1;
		add_resource(&sq->content, FOOD);
	}
	if (change)
	{
		to_send = gfx_bct_str(env, sq->x, sq->y);
		send_cmd_to_graphics(env, to_send);
		free(to_send);
	}
}

static void		pop_resources(t_env *e)
{
	int		i;
	int		ttl_res;

	i = 0;
	ttl_res = ttl_resource_in_inventory(&e->map.tartan[i].content);
	while (i < e->map.width * e->map.height)
	{
		pop_squar_resources(e, &e->map.tartan[i], ttl_res);
		++i;
	}
}

void			dicrease_differed_messages(t_env *e)
{
	t_list			*iter;
	t_differed_msg	*dmsg;
	int				i;

	iter = e->differed_msg;
	i = 0;
	while (iter != NULL)
	{
		dmsg = (t_differed_msg*)iter->data;
		--dmsg->countdown;
		iter = iter->next;
		if (dmsg->countdown == 0 && dmsg->recipient->type != FD_FREE)
		{
			send_cmd_to_client(dmsg->recipient, dmsg->msg);
			ft_listpop_n(&e->differed_msg, i + 1);
			free(dmsg->msg);
			free(dmsg);
		}
		else
			++i;
	}
}

void			new_turn(t_env *e)
{
	decrease_life(e);
	decrease_countdown(e);
	grow_egg(e);
	pop_resources(e);
	dicrease_differed_messages(e);
}
