/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bircd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 18:05:59 by rfrey             #+#    #+#             */
/*   Updated: 2015/12/14 20:03:38 by gbersac          ###   ########.fr       */
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

/*
** Type of the client.
*/
typedef enum	e_fd_type
{
	FD_FREE,
	FD_SERV,
	FD_CLIENT,
	FD_GRAPHIC
}				t_fd_type;

/*
** There is one out of POP_STONE chance that a stone pop on a square.
*/
# define POP_STONE	10

/*
** There is one out of POP_FOOD chance that a food pop on a square.
*/
# define POP_FOOD	20

# define BUF_SIZE	4096

# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: %s port\n"

/*
** This is the informations associated with one client.
**
** fct_read: function to execute when something is read on this fd.
** fct_write: functionto execute when something is write on this fd.
*/
typedef struct		s_fd
{
	int				fd;
	t_fd_type		type;
	void			(*fct_read)();
	void			(*fct_write)();
	char			buf_read[BUF_SIZE + 1];
	int				buf_read_len;
	t_list			*to_send;
	char			*nickname;
	t_trantorian	trantor;
}					t_fd;

typedef struct		s_egg
{
	int				countdown;
	char			*team;
	int				x;
	int				y;
	int				id;
}					t_egg;

/*
** Global vars of the program.
**
** fds: array of all the possible fd. All are set to 0 except those
** 		corresponding to a client (use a lot of memory, I know).
**		The num of a trantor is the fd number of its client so that
**		fds[num trantor].trantor.number = num trantor.
** fd_read, fd_write: for the select function.
** maxfd: the highest fd (usefull for select). Number of t_fd in fds.
*/
typedef struct		s_env
{
	t_fd			*fds;
	int				port;
	int				maxfd;
	int				max;
	int				r;
	fd_set			fd_read;
	fd_set			fd_write;
	t_map			map;
	t_list			*egg;

	// ?? -> list of all trantorians
	t_list			*trant;
}					t_env;



void			ft_ferror(char *msg);
void			init_env(t_env *e);
void			main_loop(t_env *e);
void			srv_create(t_env *e, int port);
void			srv_accept(t_env *e, int s);

/*
** Function to read command comming from a client
** (either graphic or normal client).
*/
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

/*
** Send cmd to the client fd. Add the \n at the end.
*/
void			send_cmd_to_client(t_fd *fd, char *str);

/*
** Send str to all the graphics client connected to this server.
** Add the \n at the end.
*/
void			send_cmd_to_graphics(t_env *env, char *str);
void			send_cmd_to_all(t_env *env, char *str);

int				is_in_team(t_trantorian *trantor, t_team team);
t_team			test_for_victory(t_env *env);
int				nb_idle_trantor(t_env *env, t_team team);
int				team_exist(t_env *env, t_team team);

#endif
