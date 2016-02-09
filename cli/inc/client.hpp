/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:18:40 by flime             #+#    #+#             */
/*   Updated: 2015/11/30 17:18:52 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <string>
# include <iostream>

extern "C" {
	# include "list.h"
	# include "general.h"
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <sys/select.h>
	#include <sys/socket.h>
}

# define BUF_SIZE	4096

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef struct	s_env
{
	char		*teamname;
	char		*hostname;
	int			port;
	int			sock;
	t_list		*buf_read;
	t_list		*buf_write;
	int			n_client;
	int			pos_x;
	int			pos_y;
	char		*last_cmd;
}				t_env;

void			ft_ferror(std::string msg);
void			init_env(t_env *env);
void			free_env(t_env *env);
int				connect_to_server(char *ip, int port);
void			main_loop(t_env *env);
void			send_cmd_to_server(t_env *env, std::string str);

/* ************************************************************************** */
/* Commands                                                                   */
/* ************************************************************************** */

typedef int (*t_cmd_fct)(t_env *env, char *cmd);

/*
** This is one of the command that can be executed by a player.
**
** label: Name of that command.
** fct: the function to execute to execute that command.
** time: time it take to execute that command.
*/
typedef struct	s_cmd
{
	char		*label;
	t_cmd_fct	fct;
	int			time;
}				t_cmd;

int				interpret_cmd(t_env *e, char *cmd);

#endif
