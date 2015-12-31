/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/07 20:37:58 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/06 22:43:04 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stdio.h>
# include "bircd.h"
# include "libft.h"

typedef int (*t_cmd_fct)(t_env *env, t_fd *fd, char *cmd);

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

/*
** A command return 0 if successful, -1 otherwise
*/

/*
** Commands to clients
*/
int				ser_avance(t_env *env, t_fd *fd, char *cmd);
int				ser_droite(t_env *env, t_fd *fd, char *cmd);
int				ser_gauche(t_env *env, t_fd *fd, char *cmd);
int				ser_voir(t_env *env, t_fd *fd, char *cmd);
int				ser_inventaire(t_env *env, t_fd *fd, char *cmd);
int				ser_prend(t_env *env, t_fd *fd, char *cmd);
int				ser_pose(t_env *env, t_fd *fd, char *cmd);
int				ser_expulse(t_env *env, t_fd *fd, char *cmd);
int				ser_broadcast(t_env *env, t_fd *fd, char *cmd);
int				ser_incantation(t_env *env, t_fd *fd, char *cmd);
int				ser_fork(t_env *env, t_fd *fd, char *cmd);
int				ser_connect_nbr(t_env *env, t_fd *fd, char *cmd);
int				ser_connect_nbr(t_env *env, t_fd *fd, char *cmd);
int				ser_begin_info(t_env *env, t_fd *fd, char *cmd);

/*
** Spontaneous (message send which are not response to the client)
** commands to graphics.
*/
int				gfx_pex(t_env *env, t_fd *fd);
int				gfx_pbc(t_env *env, t_fd *fd, char *msg);
int				gfx_pic(t_env *env, t_list *trantors);
int				gfx_pie(t_env *env);
int				gfx_pfk(t_env *env);
int				gfx_pdr(t_env *env);
//int				gfx_pgt(t_env *env);
int				gfx_pgt(t_env *env, int trantor_id, int ressource_number);
int				gfx_pdi(t_env *env);
int				gfx_enw(t_env *env);
int				gfx_eht(t_env *env);
int				gfx_ebo(t_env *env);
int				gfx_edi(t_env *env);
int				gfx_seg(t_env *env);
int				gfx_smg(t_env *env);

/*
** Commands to graphics.
*/
int				gfx_msz(t_env *env, t_fd *fd, char *cmd);
int				gfx_bct(t_env *env, t_fd *fd, char *cmd);
int				gfx_mct(t_env *env, t_fd *fd, char *cmd);
int				gfx_tna(t_env *env, t_fd *fd, char *cmd);
int				gfx_ppo(t_env *env, t_fd *fd, char *cmd);
int				gfx_plv(t_env *env, t_fd *fd, char *cmd);
int				gfx_pin(t_env *env, t_fd *fd, char *cmd);
int				gfx_sgt(t_env *env, t_fd *fd, char *cmd);
int				gfx_sst(t_env *env, t_fd *fd, char *cmd);

/*
** Graphics commands callable from other part of code.
*/
int				gfx_bct_call(t_env *env, t_fd *fd, int x, int y);
char			*gfx_bct_str(t_env *env, int x, int y);

int				interpret_cmd(t_env *e, t_fd *fd, char *cmd);

/*
** find source sound direction from dst point of view
*/
int				get_sound_dir(t_trantorian src, t_trantorian dst, t_map map);

#endif
