/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 19:02:16 by gbersac           #+#    #+#             */
/*   Updated: 2015/11/30 20:21:57 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include <stdio.h>
# include <stdlib.h>

# include "libft.h"
# include "list.h"

# define MSG_WELCOME	"BIENVENUE"
# define MSG_DEAD		"mort"
# define MSG_BROADCAST	"message"
# define MSG_OK			"ok"
# define MSG_KO			"ko"

typedef enum	e_resource
{
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME,
	FOOD,
	EGG,
	PLAYER
}				t_resource;

typedef struct	s_resourcd_lst
{
	t_resource	type;
	char		*label;
}				t_resource_lst;

typedef enum	e_direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	CENTER
}				t_direction;

# define LIFE_LONG		126
# define INIT_LIFE		10

typedef struct	s_trantorian
{
	int			health_point;
	int			pos_x;
	int			pos_y;
	t_list		*inventory;
	int			level;
	t_direction	direction;

	/*
	** Time before the trantor is allow to do something.
	*/
	int			countdown;
}				t_trantorian;

void			init_trantorian(t_trantorian *trantor);

/*
** List of all the types of resources in the game. List of t_ressource_lst.
*/
t_list			*get_lst_resource(void);
t_resource		str_to_resource(char *res);
char			*resource_to_str(t_resource res);
void			add_resource(t_list **lst, t_resource res);
int				del_resource(t_list **lst, t_resource res);
int				has_resource(t_list *lst_res, t_resource res);

#endif
