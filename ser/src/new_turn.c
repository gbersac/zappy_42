/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_turn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 22:22:49 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/18 17:07:37 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void		trantor_dead(t_env *env, int cs, t_fd *fd)
{
	ft_listpushback(&fd->to_send, strdup(MSG_DEAD));
	printf("Trantor num %d is dead\n", cs);
	close_connection(env, cs);
}

static void		grow_egg(t_env *e)
{
	t_egg	*egg;
	t_list	*tmp;

	tmp = e->egg;
	if (tmp)
	{
		while (tmp)
		{
			egg = (t_egg*)(tmp->data);
			if (egg->countdown > 0)
			{
				--egg->countdown;
				// printf("%d egg %d x:%d y:%d countdown : %d\n", i, egg->id, egg->x, egg->y,egg->countdown);
				if (egg->countdown == 0)
				{
						if (tmp->next)
					{
						ft_listpop(&tmp);
						continue ;
					}
					printf("egg is now fully grown and removed\n");
				}
			}
			tmp = tmp->next;
		}
	}
}

static void		set_egg(t_env *e, int id)
{
	t_egg	*egg;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = e->egg;
	if (tmp)
	{
		while (tmp)
		{
			egg = (t_egg*)(tmp->data);
			if (egg->countdown == 0 && egg->id == id)
			{
				printf("EGG READY !\n");
				egg->countdown = 600;
			}
			i++;
			tmp = tmp->next;
		}
	}
	printf("number of eggs : %d\n", i);
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
			if (trantor->health_point == 0)
				trantor_dead(e, i, &e->fds[i]);
			else if (trantor->countdown > 0){
				--trantor->countdown;
				// printf("trantor->countdown : %d\n", trantor->countdown);
				if (trantor->countdown == 0)
				{
					if (trantor->laying == 1)
					{
						trantor->laying = 0;
						set_egg(e, trantor->id);
					}
					printf("trantor %d is now ready to work !\n", trantor->id);
				}
			}
		}
		++i;
	}
}

static void	pop_squart_resources(t_env *env, t_square *sq)
{
	int		rdm;
	int		change;
	char	*to_send;

	rdm = rand();
	change = 0;
	if (!(rdm % POP_STONE))
	{
		change = 1;
		add_resource(&sq->content, rdm % 6 + 1);
	}
	if (!(rdm % POP_FOOD))
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

static void	pop_resources(t_env *e)
{
	int		i;
	int		ttl_res;

	i = 0;
	while (i < e->map.width * e->map.height)
	{
		ttl_res = ttl_resource_in_inventory(&e->map.tartan[i].content);
		if (ttl_res < MAX_RES_SQUARE)
			pop_squart_resources(e, &e->map.tartan[i]);
		++i;
	}
}

void		new_turn(t_env *e)
{
	send_cmd_to_clients(e, "newturn");
	decrease_life(e);
	grow_egg(e);
	pop_resources(e);
}
