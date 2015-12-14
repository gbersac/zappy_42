/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 22:35:26 by rfrey             #+#    #+#             */
/*   Updated: 2015/12/14 20:14:47 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <stdlib.h>
	#include <unistd.h>
	#include "libft.h"
	#include "general.h"
}

#include "client.hpp"

void	handle_action(t_env *env)
{
//	env->last_cmd = ...;
	++env;
}

void	player_dies(t_env *env, char *get)
{
	ft_printf("Player dies\n");
	close(env->sock);
	free(get);
	free_env(env);
	exit(EXIT_SUCCESS);
}

void	valid_last_action(t_env *env)
{
	++env;
}

void	interpret_msg(t_env *env, char *get)
{
	char	*to_send;

	if (ft_strnequ(get, MSG_WELCOME, ft_strlen(MSG_WELCOME)))
	{
		asprintf(&to_send, "%s %s\n", CMD_BEGIN_INFO, env->trantor.team);
		ft_listpushback(&env->buf_write, to_send);
		env->last_cmd = strdup(to_send);
	}
	if (ft_strnequ(get, CMD_BEGIN_INFO, ft_strlen(CMD_BEGIN_INFO)))
	{
		int ret = sscanf(get, "begin_info %d %d %d\n",
				&env->nb_free_trantor,
				&env->trantor.pos_x,
				&env->trantor.pos_x);
		if (ret < 3)
		{
			printf("Team error: %s\n", get + 11);
		}
	}
	if (ft_strnequ(get, MSG_DEAD, ft_strlen(MSG_DEAD)))
		player_dies(env, get);
	else if (ft_strnequ(get, MSG_BROADCAST, ft_strlen(MSG_BROADCAST)))
	{
		ft_printf("Get a broadcast : <%s>\n", get);
		// des trucs
	}
	else if (ft_strnequ(get, MSG_OK, ft_strlen(MSG_OK)))
	{
		valid_last_action(env);
		handle_action(env);
	}
	else if (ft_strnequ(get, MSG_KO, ft_strlen(MSG_KO)))
	{
		ft_printf("Last action fail\n");
		handle_action(env);
	}
}

void	play(t_env *env)
{
	char	*get;

	get = (char*)ft_listpop(&env->buf_read);
	ft_putendl(get);
	interpret_msg(env, get);
	free(get);
}
