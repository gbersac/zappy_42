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
# include "list.h"
# include "general.h"

# define BUF_SIZE	4096

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef struct	s_env
{
	char			*hostname;
	int				port;
	int				sock;
	t_list			*buf_read;
	t_list			*buf_write;
	int				n_client;
	char			*last_cmd;

	/*
	** Number of client that could be accepted by server.
	*/
	int				nb_free_trantor;
	t_trantorian	trantor;
}				t_env;

void			ft_ferror(std::string msg);
void			init_env(t_env *env);
void			free_env(t_env *env);
int				connect_to_server(char *ip, int port);
void			main_loop(t_env *env);
void			play(t_env *env);

#endif
