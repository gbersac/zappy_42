/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_begin_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:16:37 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/19 18:56:13 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int		test_client(t_env *env, t_fd *fd, t_team team_name)
{
	char	*to_send;

	if (!team_exist(env, team_name))
	{
		asprintf(&to_send, "%s unknown team", CMD_BEGIN_INFO);
		send_cmd_to_client(fd, to_send);
		free(to_send);
		return (-1);
	}
	if (available_connexion(env, team_name) <= 0)
	{
		asprintf(&to_send, "%s no place in this team", CMD_BEGIN_INFO);
		send_cmd_to_client(fd, to_send);
		free(to_send);
		return (-1);
	}
	return (0);
}

static void		take_idle_trantor2(t_env *env, t_fd *fd, t_team team_name)
{
	char			*to_send;

	asprintf(&to_send, "%s %d %d %d",
			CMD_BEGIN_INFO, fd->trantor.pos_x, fd->trantor.pos_y,
			available_connexion(env, team_name));
	send_cmd_to_client(fd, to_send);
	free(to_send);
	asprintf(&to_send, "ebo %d %d %d %d %s", fd->trantor.id,
			fd->trantor.pos_x, fd->trantor.pos_y,
			fd->trantor.direction, team_name);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
}

static void		take_idle_trantor(t_env *env, t_fd *fd, t_team team_name)
{
	t_list			*iter;
	t_trantorian	*trantor;
	int				i;

	iter = env->idle_trant;
	i = 0;
	while (iter != NULL)
	{
		trantor = iter->data;
		if (strcmp(trantor->team, team_name) == 0)
		{
			fd->trantor = *trantor;
			fd->trantor.id = fd->fd;
			ft_listpop_n(&env->idle_trant, i + 1);
			take_idle_trantor2(env, fd, team_name);
			return ;
		}
		++i;
		iter = iter->next;
	}
}

static void		take_initial_connect(t_env *env, t_fd *fd, t_team team_name)
{
	char	*to_send;

	--env->map.max_client;
	fd->trantor.team = strdup(team_name);
	asprintf(&to_send, "%s %d 0 0",
			CMD_BEGIN_INFO,
			available_connexion(env, team_name));
	send_cmd_to_client(fd, to_send);
	free(to_send);
	asprintf(&to_send, "pnw %d 0 0 %d 0 %s", fd->trantor.id,
			fd->trantor.direction, team_name);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
}

int				ser_begin_info(t_env *env, t_fd *fd, char *cmd)
{
	char	team_name[1024];
	sscanf(cmd, "begin_info %s\n", team_name);
	if (test_client(env, fd, team_name) == -1)
		return (-1);
	if (env->map.max_client > 0)
		take_initial_connect(env, fd, team_name);
	else
		take_idle_trantor(env, fd, team_name);
	return (0);
}
