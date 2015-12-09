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

void broadcast(t_env *env, char *str)
{
	char *ret;

	ft_putendl("broadcast");
	ret = ft_strjoin("broadcast ", str);
	ft_listpushback(&env->buf_write, ret);
}

/* 
** prend <objet>
*/
void prend(char *str, t_env *env)
{
	char *ret;

	ft_putendl("prend");
	ret = ft_strjoin("prend ", str);
	ft_listpushback(&env->buf_write, ret);
}

/* 
** pose <objet>
*/
void pose(char *str, t_env *env)
{
	char *ret;

	ft_putendl("pose");
	ret = ft_strjoin("pose ", str);
	ft_listpushback(&env->buf_write, ret);
}

void inventaire(t_env *env)
{
	ft_listpushback(&env->buf_write, "inventaire");
}

void parse_voir(char *str, t_env *env)
{
	char *without_bracket;
	char **astr;
	char **case_astr;
	int i;

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
	inventaire(env);// test a delete
}

void print_inventaire(t_env *env)
{
	ft_putendl("");ft_putnbr(env->inventory.nb_food);
	ft_putendl("");ft_putnbr(env->inventory.nb_linemate);
	ft_putendl("");ft_putnbr(env->inventory.nb_deraumere);
	ft_putendl("");ft_putnbr(env->inventory.nb_sibur);
	ft_putendl("");ft_putnbr(env->inventory.nb_mendiane);
	ft_putendl("");ft_putnbr(env->inventory.nb_phiras);
	ft_putendl("");ft_putnbr(env->inventory.nb_thystame);
	ft_putendl("");
}

/*
** Takes a string of the inventory in the form :
** %d         %d       %d       %d    %d       %d     %d
** nourriture linemate deraumes sibur mendiane phiras thystame
**
** and fill the inventory
*/

void parse_inventaire(char *str, t_env *env)
{
	char **astr;

	astr = ft_strsplit(str, ' ');
	env->inventory.nb_food = ft_atoi(astr[0]);
	env->inventory.nb_linemate = ft_atoi(astr[1]);
	env->inventory.nb_deraumere = ft_atoi(astr[2]);
	env->inventory.nb_sibur = ft_atoi(astr[3]);
	env->inventory.nb_mendiane = ft_atoi(astr[4]);
	env->inventory.nb_phiras = ft_atoi(astr[5]);
	env->inventory.nb_thystame = ft_atoi(astr[6]);
	print_inventaire(env);
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
		ft_strnequ(get, MSG_KO, ft_strlen(MSG_KO)) ||
		ft_strnequ(get, MSG_INCANTATION_2, ft_strlen(MSG_INCANTATION_2)))
	{
		ft_putendl(get); //list des requetes en cours
		tmp = (char *)ft_listpop(&env->buf_pending);
	}
	else if (ft_strnequ(get, MSG_INCANTATION_1, ft_strlen(MSG_INCANTATION_1)))
	{
		ft_putendl(get); //list des requetes en cours
		tmp = (char *)ft_listpop(&env->buf_pending);
		env->n_request++;
	}
	else if (get[0] == '{' && ft_isalpha(get[1]))
		parse_voir(get, env);
	else if (env->status > 0 && ft_isdigit(get[0]))
	{
		ft_putendl("parse_inventaire");
		ft_putendl(get);
		parse_inventaire(get, env);
	}
	else if (ft_strnequ(get, MSG_BROADCAST, ft_strlen(MSG_BROADCAST))) //msg should never start with a number
	{
		interpret_broadcast(get, env);
		ft_printf("[broadcast]: <%s>\n", get);
		env->n_request++;
	}
	else if (ft_strnequ(get, MSG_DEAD, ft_strlen(MSG_DEAD)))
		player_dies(env, get);
	else if (ft_strnequ(get, MSG_WELCOME, ft_strlen(MSG_WELCOME)))
	{
		ft_listpushback(&env->buf_write, ft_strjoin(env->teamname, "\n"));
		broadcast(env, "Je suis là");
	}
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
