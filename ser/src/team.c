/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/06 20:58:22 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/06 22:05:31 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int				is_in_team(t_trantorian *trantor, t_team team)
{
	if (trantor->team == NULL)
		return (0);
	return (strcmp(trantor->team, team) == 0);
}

static char		*test_for_victory2(t_env *env, t_team team)
{
	char	*to_send;

	asprintf(&to_send, "seg %s", team);
	send_cmd_to_all(env, to_send);
	free(to_send);
	printf("Team %s is victorious !\n", team);
	exit(EXIT_SUCCESS);
	return (team);
}

t_team			test_for_victory(t_env *env)
{
	t_list		*iter;
	t_team		team;
	int			i;
	int			winners;

	iter = env->map.teams;
	while (iter != NULL)
	{
		team = iter->data;
		i = 0;
		winners = 0;
		while (i < env->maxfd)
		{
			if (env->fds[i].type == FD_CLIENT &&
					is_in_team(&env->fds[i].trantor, team) &&
					env->fds[i].trantor.level == NB_LEVEL)
				++winners;
			++i;
		}
		if (winners >= NB_TRANTOR_VICTORY)
			return (test_for_victory2(env, team));
		iter = iter->next;
	}
	return (NULL);
}

int				available_connexion(t_env *env, t_team team)
{
	t_list			*iter;
	t_trantorian	*trant;
	int				to_return;

	iter = env->idle_trant;
	to_return = 0;
	if (env->map.max_client > 0)
		to_return = env->map.max_client;
	while (iter != NULL)
	{
		trant = (t_trantorian*)iter->data;
		if (strcmp(trant->team, team) == 0)
			++to_return;
		iter = iter->next;
	}
	return (to_return);
	team = NULL;
}

int				team_exist(t_env *env, t_team team)
{
	t_list	*iter;
	t_team	iter_team;

	iter = env->map.teams;
	while (iter != NULL)
	{
		iter_team = (t_team)iter->data;
		if (strcmp(team, iter_team) == 0)
			return (1);
		iter = iter->next;
	}
	return (0);
}
