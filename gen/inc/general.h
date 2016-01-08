/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 19:02:16 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/06 21:00:10 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include <stdio.h>
# include <stdlib.h>

# include "libft.h"
# include "list.h"

# define CMD_AVANCE				"avance"
# define CMD_AVANCE_TIME		7
# define CMD_DROITE				"droite"
# define CMD_DROITE_TIME		7
# define CMD_GAUCHE				"gauche"
# define CMD_GAUCHE_TIME		7
# define CMD_VOIR				"voir"
# define CMD_VOIR_TIME			7
# define CMD_INVENTAIRE			"inventaire"
# define CMD_INVENTAIRE_TIME	1
# define CMD_PREND				"prend"
# define CMD_PREND_TIME			7
# define CMD_POSE				"pose"
# define CMD_POSE_TIME			7
# define CMD_EXPULSE			"expulse"
# define CMD_EXPULSE_TIME		7
# define CMD_BROADCAST			"broadcast"
# define CMD_BROADCAST_TIME		7
# define CMD_INCANTATION		"incantation"
# define CMD_INCANTATION_TIME	300
# define CMD_FORK				"fork"
# define CMD_FORK_TIME			42
# define CMD_HATCHING_TIME		600
# define CMD_CONNECT_NBR		"connect_nbr"
# define CMD_CONNECT_NBR_TIME	0
# define CMD_BEGIN_INFO			"begin_info"
# define CMD_BEGIN_INFO_TIME	0
# define CMD_INVENTORY			"inventaire"
# define CMD_INVENTORY_TIME		1

# define MSG_WELCOME		"BIENVENUE"
# define MSG_DEAD			"mort"
# define MSG_BROADCAST		"message"
# define MSG_EXPULSE		"deplacement"
# define MSG_OK				"ok"
# define MSG_KO				"ko"
# define MSG_INCANTATION_1	"elevation en cours"
# define MSG_INCANTATION_2  "niveau actuel : "

typedef enum	e_resource
{
	FOOD,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME,
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
	NONEDIR,
	NORTH,
	EAST,
	SOUTH,
	WEST
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

typedef struct	s_inventory
{
	int			nb_food;
	int			nb_linemate;
	int			nb_deraumere;
	int			nb_sibur;
	int			nb_mendiane;
	int			nb_phiras;
	int			nb_thystame;
}				t_inventory;

typedef char*	t_team;

typedef struct	s_trantorian
{
	int			health_point;
	int			pos_x;
	int			pos_y;
	t_team		team;
 	int			level;
	t_direction	direction;
	t_inventory	inventory;

	/*
	** Time before the trantor is allow to do something.
	*/
	int			countdown;

	/*
	** Boolean value for trantorian laying an egg
	** 1 : he is laying, 0 : he isn't
	*/
	int			laying;

	/*
	** This is the number of the trantorian. It correspond to the fd num of
	** the client.
	** If trantorian is not associated to a fd, its id is -1
	*/
	int			id;
}				t_trantorian;

void			init_trantorian(t_trantorian *trantor, int id);

/*
** List of all the types of resources in the game. List of t_ressource_lst.
*/
t_list			*get_lst_resource(void);
t_resource		str_to_resource(char *res);
char			*resource_to_str(t_resource res);
char			*resources_to_str(t_list *lst_res);
void			add_resource(t_inventory *inv, t_resource res);
int				del_resource(t_inventory *inv, t_resource res);
int				ttl_resource_in_inventory(t_inventory *inv);

/*
** Return the number of resource of type res in the inventory.
** Return -1 if unknow ressource.
*/
int				nb_res_in_inventory(t_inventory *inv, t_resource res);

/*
** Return the number associated with a direction according to the zappy spec.
** see protocol-client-graphique-zappy.pdf
*/
int				direction_to_nbr(t_direction dir);

/*
** Return a string of the inventory in the form :
** %d         %d       %d       %d    %d       %d     %d
** nourriture linemate deraumes sibur mendiane phiras thystame
**
** The returned string have to be freed.
*/
char			*inventory_to_str(t_inventory *inv);

/*
** Reverse of inventory_to_str.
*/
t_inventory		str_to_inventory(char *str);

#endif
