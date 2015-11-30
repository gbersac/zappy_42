/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 16:55:21 by rfrey             #+#    #+#             */
/*   Updated: 2014/06/11 20:42:22 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdlib.h>

# include "list.h"

# define BUF_SIZE	4096

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef struct	s_env
{
	char	*teamname;
	char	*hostname;
	int		port;
	int		sock;
	t_list	*buf_read;
	t_list	*buf_write;
	int		n_client;
	int		pos_x;
	int		pos_y;
	char	*last_cmd;
}				t_env;

typedef void (*t_cmd_fct)(t_env *env, char *cmd);

typedef struct	s_cmd
{
	char		*label;
	t_cmd_fct	fct;
}				t_cmd;

void			ft_ferror(char *msg);
void			init_env(t_env *env);
void			free_env(t_env *env);
int				connect_to_server(char *ip, int port);
void			main_loop(t_env *env);
void			play(t_env *env);
t_list			*get_lst_cmd(void);

void			gfx_msz(t_env *env, char *cmd);
void			gfx_bct(t_env *env, char *cmd);
void			gfx_bct(t_env *env, char *cmd);
void			gfx_tna(t_env *env, char *cmd);
void			gfx_pnw(t_env *env, char *cmd);
void			gfx_ppo(t_env *env, char *cmd);
void			gfx_plv(t_env *env, char *cmd);
void			gfx_pin(t_env *env, char *cmd);
void			gfx_pex(t_env *env, char *cmd);
void			gfx_pbc(t_env *env, char *cmd);
void			gfx_pic(t_env *env, char *cmd);
void			gfx_pie(t_env *env, char *cmd);
void			gfx_pfk(t_env *env, char *cmd);
void			gfx_pdr(t_env *env, char *cmd);
void			gfx_pgt(t_env *env, char *cmd);
void			gfx_pdi(t_env *env, char *cmd);
void			gfx_enw(t_env *env, char *cmd);
void			gfx_eht(t_env *env, char *cmd);
void			gfx_ebo(t_env *env, char *cmd);
void			gfx_edi(t_env *env, char *cmd);
void			gfx_sgt(t_env *env, char *cmd);
void			gfx_sgt(t_env *env, char *cmd);
void			gfx_seg(t_env *env, char *cmd);
void			gfx_smg(t_env *env, char *cmd);
void			gfx_suc(t_env *env, char *cmd);
void			gfx_sbp(t_env *env, char *cmd);

#endif
