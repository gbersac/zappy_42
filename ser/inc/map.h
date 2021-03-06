/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:34:05 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/05 17:02:59 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define MAX_RES_SQUARE	5

# include "general.h"

typedef struct	s_square
{
	int			x;
	int			y;
	t_inventory	content;
}				t_square;

/*
** time_d: Time divisor (option -t).
** tartan:	Pointer to the table of square which is the map.
** 			Case numerotation is :
** 			0 1 2
** 			3 4 5...
*/
typedef struct	s_map
{
	int			width;
	int			height;
	t_list		*teams;
	int			time_d;
	int			max_client;
	t_square	*tartan;
}				t_map;

struct s_env;

t_square		*get_square(struct s_env *e, int x, int y);
void			gen_map(struct s_env *e);
int				adjust_coord(int coord, int ref);
char			*resource_to_str(t_resource res);

#endif
