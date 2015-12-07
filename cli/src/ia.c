/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 22:35:26 by rfrey             #+#    #+#             */
/*   Updated: 2014/06/05 00:05:40 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "client.h"
#include "libft.h"
#include "general.h"

void	handle_action(t_env *env)
{
//	env->last_cmd = ...;
	++env;
}

void	get_server_param(t_env *env)
{
	char	*get;
	char	**pos;

	get = (char*)ft_listpop(&env->buf_read);
	// ft_putstr("1");ft_putendl(get);
	env->n_client = ft_atoi(get);
	free(get);
	get = (char*)ft_listpop(&env->buf_read);
	// ft_putstr("2");ft_putendl(get);
	pos = ft_strsplit(get, ' ');
	if (!pos || ft_strtabsize(pos) < 2)
		ft_ferror("Wrong coordinate msg");
	env->pos_x = ft_atoi(pos[0]);
	env->pos_y = ft_atoi(pos[1]);
	free(get);
	ft_strtabfree(&pos);
	handle_action(env);
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
	if (ft_strnequ(get, MSG_WELCOME, ft_strlen(MSG_WELCOME)))
	{
		ft_listpushback(&env->buf_write, env->teamname);
		env->last_cmd = MSG_WELCOME;
	}
	else if (ft_strnequ(get, MSG_DEAD, ft_strlen(MSG_DEAD)))
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

	if (ft_strnequ(env->last_cmd, MSG_WELCOME, ft_strlen(MSG_WELCOME)))
	{
		if (ft_listcnt(env->buf_read) >= 2)
			get_server_param(env);
		return ;
	}
	get = (char*)ft_listpop(&env->buf_read);
	// ft_putendl(get);
	interpret_msg(env, get);
	free(get);
}
