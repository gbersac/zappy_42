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

static void get_nb_client(t_env *env, char *get)
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
		exit(0);
	}
}

static void get_xy(t_env *env, char *get)
{
	char	**pos;
	int		len;

	pos = ft_strsplit(get, ' ');
	len = ft_strtabsize(pos);
	if (pos && len == 2 && ft_strisdigit(pos[0]) && ft_strisdigit(pos[1]))
	{
		env->pos_x = ft_atoi(pos[0]);
		env->pos_y = ft_atoi(pos[1]);
		ft_printf("[coords]: %d, %d\n", env->pos_x, env->pos_y);
		env->n_request++;
	}
	else
	{
		ft_ferror("error: get_xy()");
		exit(0);
	}
}

void		interpret_msg_init(t_env *env, char *get)
{
	if (env->status == status_welcome && ft_strnequ(get, MSG_WELCOME, ft_strlen(MSG_WELCOME)))
		cmd(env, env->trantor.team, "");
	else if (env->status == status_nb_client)
		get_nb_client(env, get);
	else if (env->status == status_xy)
		get_xy(env, get);
	env->status++;
}

static void	player_dies(t_env *env, char *get)
{
	ft_printf("Player dies\n");
	close(env->sock);
	free(get);
	free_env(env);
	exit(EXIT_SUCCESS);
}

void		interpret_broadcast()
{
	ft_putendl("interpret_broadcast");
}

void		interpret_expulse()
{
	ft_putendl("interpret_expulse");
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



void ia(t_env *env)
{
	if (env->status == status_avance)
		cmd(env, CMD_AVANCE, "");
	else if (env->status == status_droite)
		cmd(env, CMD_DROITE, "");
	else if (env->status == status_gauche)
		cmd(env, CMD_GAUCHE, "");
	else if (env->status == status_voir)
		cmd(env, CMD_VOIR, "");
	else if (env->status == status_inventaire)
		cmd(env, CMD_INVENTAIRE, "");
	else if (env->status == status_prend)
		cmd(env, CMD_PREND, " 0");
	else if (env->status == status_pose)
		cmd(env, CMD_POSE, " 0");
	// else if (env->status == status_expulse) //manque le retour ok???
	// 	cmd(env, CMD_EXPULSE, "");
	else if (env->status == status_broadcast)
		cmd(env, CMD_BROADCAST, " Je suis là");
	else if (env->status == status_incantation)
		cmd(env, CMD_INCANTATION, "");
	else if (env->status == status_fork)
		cmd(env, CMD_FORK, "");
	else if (env->status == status_connect_nbr)
		cmd(env, CMD_CONNECT_NBR, "");
}

void		interpret_msg(t_env *env, char *get)
{
	// char	*tmp;

	ft_putstr("interpret_msg: ");
	ft_putendl(get);

	if (interpret_msg_okko(env, get))
	{
		ft_putendl("ok/ko");
		env->status++;
	}
	else if (ft_strnequ(get, MSG_INCANTATION_2, ft_strlen(MSG_INCANTATION_2)))
		env->status++;
	else if (ft_strnequ(get, MSG_INCANTATION_1, ft_strlen(MSG_INCANTATION_1)))
		;
	else if (ft_isdigit(get[0]))
	{
		get_nb_client(env, get);
		env->status++;
	}
	else if (get[0] == '{' && ft_isdigit(get[1]))
	{
		parse_voir(env, get);
		env->status++;
	}
	else if (ft_strnequ(get, CMD_INVENTAIRE, ft_strlen(CMD_INVENTAIRE)))
	{
		parse_inventaire(env, get);
		env->status++;
	}
	else if (ft_strnequ(get, MSG_BROADCAST, ft_strlen(MSG_BROADCAST))) //msg should never start with a number
	{
		interpret_broadcast();
	}
	else if (ft_strnequ(get, MSG_DEAD, ft_strlen(MSG_DEAD)))
		player_dies(env, get);
	else if (ft_strnequ(get, MSG_EXPULSE, ft_strlen(MSG_EXPULSE)))
		interpret_expulse();
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
	if (env->status <= status_xy)
		interpret_msg_init(env, get);
	else
		interpret_msg(env, get);
	
	ia(env);
	free(get);
}
