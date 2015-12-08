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

int	ft_strisdigit(char *str)
{
	int	i;

	i = (str[0] == '-' || str[0] == '+') ? 1 : 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
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

void	interpret_msg(t_env *env, char *get)
{
	if (ft_strnequ(get, MSG_OK, ft_strlen(MSG_OK)))
	{
		ft_putendl("[ok]");
	}
	else if (ft_strnequ(get, MSG_KO, ft_strlen(MSG_KO)))
	{
		ft_putendl("[ko]");
	}
	else if (ft_strnequ(get, MSG_BROADCAST, ft_strlen(MSG_BROADCAST))) //msg should never start with a number
	{
		ft_printf("[broadcast]: <%s>\n", get);
	}
	else if (ft_strnequ(get, MSG_DEAD, ft_strlen(MSG_DEAD)))
		player_dies(env, get);
	else if (ft_strnequ(get, MSG_WELCOME, ft_strlen(MSG_WELCOME)))
		ft_listpushback(&env->buf_write, ft_strjoin(env->teamname, "\n"));
	else if (get_server_param(get, env))
		;
}

void	play(t_env *env)
{
	char	*get;

	get = (char*)ft_listpop(&env->buf_read);
	interpret_msg(env, get);
	free(get);
}
