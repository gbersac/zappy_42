/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bircd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 18:05:59 by rfrey             #+#    #+#             */
/*   Updated: 2014/06/10 21:53:24 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIRCD_H
# define BIRCD_H

# include <sys/select.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/timeb.h>
# include <time.h>
# include <sys/socket.h>

# include "list.h"
# include "libft.h"
# include "general.h"

# include "map.h"
# include "incantation.h"

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

/*
** There is one out of POP_STONE chance that a stone pop on a square.
** There is one out of POP_FOOD chance that a food pop on a square.
*/
# define POP_STONE	10
# define POP_FOOD	20

# define BUF_SIZE	4096

# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: %s port\n"

typedef struct	s_fd
{
	int				type;
	void			(*fct_read)();
	void			(*fct_write)();
	char			buf_read[BUF_SIZE + 1];
	int				buf_read_len;
	t_list			*to_send;
	char			*nickname;
	t_trantorian	trantor;
}				t_fd;

typedef struct	s_env
{
	t_fd	*fds;
	int		port;
	int		maxfd;
	int		max;
	int		r;
	fd_set	fd_read;
	fd_set	fd_write;
	t_map	map;
}				t_env;

void			ft_ferror(char *msg);
void			init_env(t_env *e);
void			main_loop(t_env *e);
void			srv_create(t_env *e, int port);
void			srv_accept(t_env *e, int s);
void			client_read(t_env *e, int cs);
void			clean_fd(t_fd *fd);
void			do_select(t_env *e);
int				send_private_msg(t_env *e, int cs, char *cmd);
int				cmd_msg_error(t_env *e, int cs, char *error);
int				update_env(t_env *e, char **av);
int				get_num_turn(t_env *env);
long long		get_time_now(void);
void			new_turn(t_env *e);
void			close_connection(t_env *e, int cs);
void			avance_trantor(t_env *env,
								t_trantorian	*trantor,
								t_direction dir);

#endif
