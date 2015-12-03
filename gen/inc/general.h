/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 19:02:16 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/03 13:34:48 by gbersac          ###   ########.fr       */
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

/*
** Orientation of a trantorian. Do not change the order of the directions !
*/
typedef enum	e_direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
}				t_direction;

typedef enum	e_sound_dir
{
	U,
	R,
	D,
	L,
	C
}				t_sound_dir;

# define LIFE_LONG		126
# define INIT_LIFE		10

typedef struct	s_trantorian
{
	int			health_point;
	int			pos_x;
	int			pos_y;
	char		*team;
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
char			*resources_to_str(t_list *lst_res);
void			add_resource(t_list **lst, t_resource res);
int				del_resource(t_list **lst, t_resource res);

/*
** Return the number of resource of type res in the inventory.
*/
int				nb_res_in_inventory(t_resource res, t_list *inventory);

/*
** Return the id of the node in the list of the resource res or -1 if threre
** is none.
*/
int				has_resource(t_list *lst_res, t_resource res);

/*
** Return the number associated with a direction according to the zappy spec.
** see protocol-client-graphique-zappy.pdf
*/
int				direction_to_nbr(t_direction dir);

#endif
