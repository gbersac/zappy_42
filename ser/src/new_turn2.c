/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_turn2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 21:17:27 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 21:22:31 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void		trantor_dead(t_env *env, int cs, t_fd *fd)
{
	char	*to_send;

	ft_listpushback(&fd->to_send, strdup(MSG_DEAD));
	printf("Trantor num %d is dead\n", cs);
	asprintf(&to_send, "pdi %d", fd->trantor.id);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
	close_connection(env, cs);
}

void		fork_player(t_env *e, t_egg *egg)
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

void		grow_egg(t_env *e)
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

void		set_egg(t_env *e, t_trantorian *trantor)
{
	t_egg	*egg;
	t_list	*tmp;
	int		i;
	char	*msg;

	trantor->laying = 0;
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

void		decrease_countdown(t_env *e)
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
					set_egg(e, trantor);
				send_cmd_to_client(&e->fds[i], MSG_OK);
			}
			else if (trantor->countdown <= -NB_TURN_BEFORE_TRANTOR_CALLBACK)
			{
				send_cmd_to_client(&e->fds[i], MSG_RELAUNCH);
			}
		}
		++i;
	}
}
