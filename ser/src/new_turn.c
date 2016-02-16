/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_turn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 22:22:49 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/18 19:36:51 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void		trantor_dead(t_env *env, int cs, t_fd *fd)
{
	char	*to_send;

	ft_listpushback(&fd->to_send, strdup(MSG_DEAD));
	printf("Trantor num %d is dead\n", cs);
	asprintf(&to_send, "pdi %d", fd->trantor.id);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
	close_connection(env, cs);
}

void				fork_player(t_env *e, t_egg *egg)
{
	t_trantorian	*trant;
	char			*msg;

	if (egg == NULL)
	{
		printf("error: null egg\n");
		return ;
	}
	trant = (t_trantorian*)malloc(sizeof(t_trantorian));
	init_trantorian(trant, -1);
	trant->direction = rand() % 4;
	trant->pos_x = egg->x;
	trant->pos_y = egg->y;
	trant->team = egg->team;
	ft_listpushback(&e->idle_trant, trant);
	asprintf(&msg, "eht %d", egg->id);
	send_cmd_to_graphics(e, msg);
	free(msg);
}

static void		grow_egg(t_env *e)
{
	t_egg	*egg;
	t_list	*iter;
	int		i;

	i = 0;
	iter = e->egg;
	while (iter)
	{
		if (!iter->data)
			continue ;
		egg = (t_egg*)(iter->data);
		iter = iter->next;
		if (egg->countdown > 0)
			--egg->countdown;
		else if (egg->countdown == 0)
		{
			printf("Egg hatching for team %s\n", egg->team);
			fork_player(e, egg);
			ft_listpop_n(&e->egg, i + 1);
			continue ;
		}
		i++;
	}
}

static void		set_egg(t_env *e, t_trantorian *trantor)
{
	t_egg	*egg;
	t_list	*tmp;
	int		i;
	char	*msg;

	i = 0;
	tmp = e->egg;
	while (tmp)
	{
		egg = (t_egg*)(tmp->data);
		if (egg->countdown == -1 && egg->id_trantor == trantor->id)
		{
			egg->countdown = CMD_HATCHING_TIME;
			egg->id = e->id_egg++;
			asprintf(&msg, "enw %d %d %d %d", egg->id, trantor->id,
					trantor->pos_x, trantor->pos_y);
			send_cmd_to_graphics(e, msg);
			free(msg);
		}
		i++;
		tmp = tmp->next;
	}
}

static void		decrease_countdown(t_env *e)
{
	int				i;
	t_trantorian	*trantor;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT)
		{
			trantor = &e->fds[i].trantor;
			--trantor->countdown;
			if (trantor->countdown == 0)
			{
				if (trantor->laying == 1)
				{
					trantor->laying = 0;
					set_egg(e, trantor);
				}
				send_cmd_to_client(&e->fds[i], MSG_OK);
				// printf("trantor %d is now ready to work !\n", trantor->id);
			}
			else if (trantor->countdown <= -NB_TURN_BEFORE_TRANTOR_CALLBACK)
			{
				send_cmd_to_client(&e->fds[i], MSG_RELAUNCH);
			}
		}
		++i;
	}
}

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
					// printf("eat food ! %d\n", trantor->health_point);
				}
				else
					trantor_dead(e, i, &e->fds[i]);
			}
		}
		++i;
	}
}

static void	pop_squar_resources(t_env *env, t_square *sq, int ttl_res)
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

static void	pop_resources(t_env *e)
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

void		dicrease_differed_messages(t_env *e)
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

void		new_turn(t_env *e)
{
	decrease_life(e);
	decrease_countdown(e);
	grow_egg(e);
	pop_resources(e);
	dicrease_differed_messages(e);
}
