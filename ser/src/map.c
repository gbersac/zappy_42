/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:33:33 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/05 16:43:50 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int				adjust_coord(int coord, int ref)
{
	coord = coord % ref;
	if (coord < 0)
		coord = ref + coord;
	return (coord);
}

t_square		*get_square(t_env *e, int x, int y)
{
	t_square	*tartan;
	int			i;

	x = adjust_coord(x, e->map.width);
	y = adjust_coord(y, e->map.height);
	tartan = e->map.tartan;
	i = e->map.width * y + x;
	return (&(tartan[i]));
}

void			gen_map(t_env *e)
{
	int			nb_square;
	int			i;
	t_square	*sq;
	t_list		*teams;

	teams = e->map.teams;
	nb_square = e->map.width * e->map.height;
	e->map.tartan = (t_square*)malloc(sizeof(t_square) * nb_square);
	bzero(e->map.tartan, sizeof(t_square) * nb_square);
	i = 0;
	while (i < nb_square)
	{
		sq = &(e->map.tartan[i]);
		sq->x = i % e->map.width;
		sq->y = i / e->map.width;
		++i;
	}
	e->map.teams = teams;
}
