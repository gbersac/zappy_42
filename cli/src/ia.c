/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 22:35:26 by flime             #+#    #+#             */
/*   Updated: 2015/12/24 22:29:55 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "general.h"
#include "client.h"

static int	get_server_param(char *get, t_env *env)
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

static void	player_dies(t_env *env, char *get)
{
	ft_printf("Player dies\n");
	close(env->sock);
	free(get);
	free_env(env);
	exit(EXIT_SUCCESS);
}

void		interpret_broadcast(t_env *env, char *get)
{
	(void)env;
	(void)get;
}


/*
** 
**
**
*/

// void	interpret_msg_digit(t_env *env, char *get)
// {

// }
static int	interpret_msg_okko(t_env *env, char *get)
{
	(void)env;
	if (ft_strnequ(get, MSG_OK, ft_strlen(MSG_OK)) ||
		ft_strnequ(get, MSG_KO, ft_strlen(MSG_KO)))
		return (1);
	return (0);
}

void		interpret_msg(t_env *env, char *get)
{
	char	*tmp;

	ft_putstr("interpret_msg: ");
	ft_putendl(get);
	if (interpret_msg_okko(env, get))
	{
<<<<<<< HEAD
		ft_putendl("okko");
		if (ft_strnequ(get, MSG_OK, ft_strlen(MSG_OK)))
		{
			ft_putendl("in");
			cmd(env, "voir", "");
		}
		else
			exit(0);
		// tmp = (char *)ft_listpop(&env->buf_pending);
		// ft_putstr("okko pop : ");
		// ft_putendl(tmp);
		// if (env->n_request == 1)
		// 	env->n_request = 0;
=======
		ft_listpushback(&env->buf_write, ft_strjoin(env->teamname, "\n"));
		env->last_cmd = MSG_WELCOME;
>>>>>>> bd513116d8b551ceee607b7df53a94940d50e019
	}
	else if (ft_strnequ(get, MSG_INCANTATION_2, ft_strlen(MSG_INCANTATION_2)))
		tmp = (char *)ft_listpop(&env->buf_pending);
	else if (ft_strnequ(get, MSG_INCANTATION_1, ft_strlen(MSG_INCANTATION_1)))
	{
		tmp = (char *)ft_listpop(&env->buf_pending);
		env->n_request++;
	}
	else if (get[0] == '{' && ft_isdigit(get[1]))
	{
		ft_putendl("{");
		parse_voir(env, get);
	}
	else if (env->status > 0 && ft_isdigit(get[0]))
		parse_inventaire(env, get);
	else if (ft_strnequ(get, MSG_BROADCAST, ft_strlen(MSG_BROADCAST))) //msg should never start with a number
	{
		interpret_broadcast(env, get);
		ft_printf("[broadcast]: <%s>\n", get);
		// env->n_request++;
	}
	else if (ft_strnequ(get, MSG_DEAD, ft_strlen(MSG_DEAD)))
		player_dies(env, get);
	else if (ft_strnequ(get, MSG_WELCOME, ft_strlen(MSG_WELCOME)))
	{
		ft_listpushback(&env->buf_write, ft_strjoin(env->teamname, "\n"));
		cmd(env, (char *)"broadcast ", (char *)"Je suis là");
	}
	else if (get[0] != '{' && get_server_param(get, env))//digit
		;
	else
		ft_printf("message %s not implemented");
	env->n_request--;
	ft_printf("n_request: %d\n", env->n_request);
	ft_printf("status: %d\n", env->status);
}

void		play(t_env *env)
{
	char	*get;

	get = (char*)ft_listpop(&env->buf_read);
	ft_putendl(get);
	interpret_msg(env, get);
	free(get);
}
