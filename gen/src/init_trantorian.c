/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_trantorian.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 18:48:38 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/05 14:46:21 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"

void			init_trantorian(t_trantorian *trantor, int id)
{
	bzero(trantor, sizeof(t_trantorian));
	trantor->health_point = LIFE_LONG * INIT_LIFE;
	trantor->pos_x = 0;
	trantor->pos_y = 0;
	trantor->level = 1;
	trantor->direction = NORTH;
	trantor->id = id;
	trantor->laying = 0;
}

int				direction_to_nbr(t_direction dir)
{
	return (dir + 1);
}
