/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 06:49:19 by flime             #+#    #+#             */
/*   Updated: 2016/01/18 20:45:06 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "general.h"
#include "client.h"

static void	get_nb_client(t_env *env, char *get)
{
	char	**pos;
	int		len;

	pos = ft_strsplit(get, ' ');
	len = ft_strtabsize(pos);
	if (pos && len == 1 && ft_strisdigit(pos[0]))
	{
		env->n_client = ft_atoi(get);
		ft_printf("[nclient]: %d\n", env->n_client);
	}
	else
	{
		ft_ferror("error: get_nb_client()");
		exit(EXIT_FAILURE);
	}
}

// static void	get_xy(t_env *env, char *get)
// {
// 	char	**pos;
// 	int		len;

// 	pos = ft_strsplit(get, ' ');
// 	len = ft_strtabsize(pos);
// 	if (pos && len == 2 && ft_strisdigit(pos[0]) && ft_strisdigit(pos[1]))
// 	{
// 		env->pos_x = ft_atoi(pos[0]);
// 		env->pos_y = ft_atoi(pos[1]);
// 	}
// 	else
// 	{
// 		ft_ferror("error: get_xy()");
// 		exit(EXIT_FAILURE);
// 	}
// }

static void	player_dies(t_env *env, char *get)
{
	ft_printf("Player dies\n");
	close(env->sock);
	free(get);
	free_env(env);
	exit(EXIT_SUCCESS);
}

/*
** interpret expected return messages
*/

static int	interpret_msg_return(t_env *env, char *get)
{
	// if (env->status == status_welcome &&
	// 		ft_strnequ(get, MSG_WELCOME, ft_strlen(MSG_WELCOME)))
	// 	cmd(env, env->trantor.team, "");
	printf("interpret_msg_return\n");
	if (ft_strnequ(get, CMD_BEGIN_INFO, ft_strlen(CMD_BEGIN_INFO)))
	{
		ft_putendl("new_begin_info");
		int ret = sscanf(get, "begin_info %d %d %d\n",
				&env->n_client,
				&env->trantor.pos_x,
				&env->trantor.pos_x);
		if (ret < 3)
		{
			printf("Team error: %s\n", get + 11);
		}
		env->n_request--;
		env->n_request--;
	}
	// else if (env->status == status_nb_client && ft_isdigit(get[0]))
	// {
	// 	get_nb_client(env, get);
	// 	env->n_request++;
	// }
	// else if (env->status == status_xy && ft_isdigit(get[0]))
	// 	get_xy(env, get);
	else if (ft_strnequ(get, MSG_OK, ft_strlen(MSG_OK)) ||
				ft_strnequ(get, MSG_KO, ft_strlen(MSG_KO))) {
		printf("OK/KO\n");
		env->n_request--;
	}
	else if (ft_strnequ(get, MSG_INCANTATION_2, ft_strlen(MSG_INCANTATION_2)))
		;
	else if (ft_isdigit(get[0]))
		get_nb_client(env, get);
	else if (get[0] == '{' && ft_isdigit(get[1])) {
		parse_voir(env, get);
		// env->n_request++;
		env->status--;
	}
	else if (ft_strnequ(get, CMD_INVENTAIRE, ft_strlen(CMD_INVENTAIRE))) {
		parse_inventaire(env, get);
		// env->n_request++;
		env->status--;
	}
	else
		return (0);
	if (env->n_request < 0)
		env->n_request = 0;
	return (1);
}

void		interpret_msg(t_env *env, char *get)
{
	printf("interpret_msg\n");
	if (interpret_msg_return(env, get))
	{
		// if (env->status <= status_xy ||
		// 	(env->status > status_xy && env->n_request == 0))
			env->status++;
	}
	else if (ft_strnequ(get, MSG_INCANTATION_1, ft_strlen(MSG_INCANTATION_1)))
		;
	else if (ft_strnequ(get, MSG_BROADCAST, ft_strlen(MSG_BROADCAST)))
		interpret_broadcast(env, get);
	else if (ft_strnequ(get, MSG_DEAD, ft_strlen(MSG_DEAD)))
		player_dies(env, get);
	else if (ft_strnequ(get, MSG_WELCOME, ft_strlen(MSG_WELCOME)))
	{
		cmd(env, "PLAYER", "");
	}
	else if (ft_strnequ(get, MSG_CONNECTED, ft_strlen(MSG_CONNECTED)))
	{
		printf("ici\n");
		char *to_send;
		asprintf(&to_send, "begin_info %s", env->trantor.team);
		cmd(env, to_send, NULL);
		free(to_send);
		env->n_request--;
	}
	else if (ft_strnequ(get, MSG_EXPULSE, ft_strlen(MSG_EXPULSE)))
		;
	else
		printf("message %s not implemented", get);
	printf("n_request: %d\n", env->n_request);
	printf("status: %d\n", env->status);
}
