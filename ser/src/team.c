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

int			is_in_team(t_trantorian *trantor, t_team team)
{
	if (trantor->team == NULL)
		return (0);
	return (strcmp(trantor->team, team) == 0);
}

t_team		test_for_victory(t_env *env)
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
			return (team);
		iter = iter->next;
	}
	return (NULL);
}
