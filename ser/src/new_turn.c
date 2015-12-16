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

void				fork_player(t_env *e, t_egg *egg)
{
	t_trantorian	*trant;

	trant = (t_trantorian*)malloc(sizeof(t_trantorian));
	init_trantorian(trant, -1);
	trant->direction = rand() % 4;
	trant->pos_x = egg->x;
	trant->pos_y = egg->y;
	trant->team = egg->team;
	printf("trant->id : %d\n", trant->id);
	printf("trant->team : %s\n", trant->team);
	ft_listpushback(&e->trant, trant);
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
			if (tmp->data)
			{
				if (egg->countdown > 0)
				{
					--egg->countdown;
					printf("egg %d x:%d y:%d countdown : %d\n", egg->id, egg->x, egg->y,egg->countdown);
					if (egg->countdown == 0)
					{
						fork_player(e, egg);
						if (tmp->next)
						{
							if (!tmp)
								printf("tmp plus LA\n");
							ft_listpop(&tmp);
							continue ;
						}
						else
						{
							if (!tmp)
								printf("tmp plus LA\n");
							free(tmp);
							e->egg = NULL;
							break;
						}
					}
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
				egg->countdown = CMD_HATCHING_TIME;
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
	// send_cmd_to_all(e, "newturn");
	decrease_life(e);
	grow_egg(e);
	pop_resources(e);
}
