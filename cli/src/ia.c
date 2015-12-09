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

/* 
** prendre takes 
*/
void prend(char *str, t_env *env)
{
	char *ret;

	ft_putendl("prend");
	ret = ft_strjoin("prend ", str);
	ft_listpushback(&env->buf_write, ret);
}

void parse_voir(char *str, t_env *env)
{
	char *without_bracket;
	char **astr;
	char **case_astr;
	int i;

	ft_putendl("parse_voir");
	ft_putendl(str);
	without_bracket = ft_strsub(str, 1, ft_strlen(str) - 2);
	ft_putendl(without_bracket);
	astr = ft_strsplit(without_bracket, ',');
	ft_strtabput(astr);
	i = 0;
	// while (astr[i])
	// {
		case_astr = ft_strsplit(astr[i], ' ');
		ft_strtabput(case_astr);
		// i++;
	// }
	i = 0;
	while (case_astr[i])
	{
		prend(case_astr[i], env);
		i++;
	}
}

void	handle_action(t_env *env)
{
	++env;
}

int		get_server_param(char *get, t_env *env)
{
	char	**pos;
	int		len;

	pos = ft_strsplit(get, ' ');
	len = ft_strtabsize(pos);
	if (pos && len == 1 && ft_strisdigit(pos[0]))
	{
		env->n_client = ft_atoi(get);
		ft_printf("[nclient]: %d\n", env->n_client);
		return (1);
	}
	else if (pos && len == 2 && ft_strisdigit(pos[0]) && ft_strisdigit(pos[1]))
	{
		env->pos_x = ft_atoi(pos[0]);
		env->pos_y = ft_atoi(pos[1]);
		ft_printf("[coords]: %d, %d\n", env->pos_x, env->pos_y);
		env->n_request++;
		env->status = voir;
		return (2);
	}
	else
	{
		ft_ferror("error: get_server_param()");
		return (0);
	}
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

void	interpret_broadcast(char *get, t_env *env)
{
	(void)env;
	(void)get;
}

void	interpret_msg(t_env *env, char *get)
{
	char *tmp;
	if (ft_strnequ(get, MSG_OK, ft_strlen(MSG_OK)) ||
		ft_strnequ(get, MSG_KO, ft_strlen(MSG_KO)))
	{
		ft_putendl(get); //list des requetes en cours
		tmp = (char *)ft_listpop(&env->buf_pending);
	}
	else if (get[0] == '{')
	{
		if (ft_isalpha(get[1]))
			parse_voir(get, env);
	}
	else if (ft_strnequ(get, MSG_BROADCAST, ft_strlen(MSG_BROADCAST))) //msg should never start with a number
	{
		interpret_broadcast(get, env);
		ft_printf("[broadcast]: <%s>\n", get);
	}
	else if (ft_strnequ(get, MSG_DEAD, ft_strlen(MSG_DEAD)))
		player_dies(env, get);
	else if (ft_strnequ(get, MSG_WELCOME, ft_strlen(MSG_WELCOME)))
		ft_listpushback(&env->buf_write, ft_strjoin(env->teamname, "\n"));
	else if (get_server_param(get, env))
		;
	env->n_request--;
	ft_printf("n_request: %d\n", env->n_request);
	ft_printf("status: %d\n", env->status);
}

void	play(t_env *env)
{
	char	*get;

	get = (char*)ft_listpop(&env->buf_read);
	interpret_msg(env, get);
	free(get);
}
