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

# include "list.h"
# include "general.h"
//# include "../../gen/inc/general.h"

# define BUF_SIZE	4096

typedef enum		e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef enum		e_status
{
	status_init,
	status_welcome,
	status_nb_client,
	status_xy,
	status_avance,
	status_droite,
	status_gauche,
	status_voir,
	status_inventaire,
	status_prend,
	status_pose,
	// status_expulse,
	status_broadcast,
	status_incantation,
	status_fork,
	status_connect_nbr
}					t_status;

typedef enum		e_role
{
	valet,
	roi
}					t_role;

typedef struct		s_env
{
	char			*teamname;
	char			*hostname;
	int				port;
	int				sock;
	t_list			*buf_read;
	t_list			*buf_write;
	t_list			*buf_pending;
	int				n_client;
	int				n_request;
	int				pos_x;
	int				pos_y;
	int				status;
	int				role;
	t_inventory		inventory;
	t_trantorian	trantor;
}				t_env;

void				ft_ferror(char *msg);
void				init_env(t_env *env);
void				free_env(t_env *env);
int					connect_to_server(char *ip, int port);
void				main_loop(t_env *env);
void				play(t_env *env);
void				send_buffer(t_env *env);
void 				cmd(t_env *env, char *cmd, char *str);
void 				parse_inventaire(t_env *env, char *str);
void 				print_inventaire(t_env *env);
void				parse_voir(t_env *env, char *str);

#endif
