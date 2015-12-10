/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sound_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 13:36:32 by flime             #+#    #+#             */
/*   Updated: 2015/12/02 13:36:36 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/map.h"
#include "../../gen/inc/general.h"

/*
** Sound direction starts from trantorian sight 1
** and rotates anticlockwise
*/

int			ft_abs(int n)
{
	return ((n < 0) ? -n : n);
}

static int	sound_direction(t_sound_dir h, t_sound_dir v, t_direction d)
{
	if (h == C && v == C)
		return (0);
	else if (h == C && v == U)
		return (1 + d * 2);
	else if (h == L && v == U)
		return (2 + d * 2);
	else if (h == L && v == C)
		return (3 + d * 2) % 8;
	else if (h == L && v == D)
		return (4 + d * 2) % 8;
	else if (h == C && v == D)
		return (5 + d * 2) % 8;
	else if (h == R && v == D)
		return (6 + d * 2) % 8;
	else if (h == R && v == C)
		return (7 + d * 2) % 8;
	else if (h == R && v == U)
		return (8 + d * 2) % 8;
	return (-1);
}

static int	sound_x(t_trantorian src, t_trantorian dst, t_map m, t_sound_dir x)
{
	if ((int)(x + x) > m.width)
	{
		if (src.pos_x < dst.pos_x)
		{
			x = src.pos_x + m.width - dst.pos_x;
			return (R);
		}
		else if (src.pos_x > dst.pos_x)
		{
			x = dst.pos_x + m.width - src.pos_x;
			return (L);
		}
		else
			return (C);
	}
	else
	{
		if (src.pos_x < dst.pos_x)
			return (L);
		else if (src.pos_x > dst.pos_x)
			return (R);
		else
			return (C);
	}
}

static int	sound_y(t_trantorian src, t_trantorian dst, t_map m, t_sound_dir y)
{
	if ((int)(y + y) > m.height)
	{
		if (src.pos_y < dst.pos_y)
		{
			y = src.pos_y + m.width - dst.pos_y;
			return (D);
		}
		else if (src.pos_y > dst.pos_y)
		{
			y = dst.pos_y + m.width - src.pos_y;
			return (U);
		}
		else
			return (C);
	}
	else
	{
		if (src.pos_y < dst.pos_y)
			return (D);
		else if (src.pos_y > dst.pos_y)
			return (U);
		else
			return (C);
	}
}

/*
** find source sound direction from dst point of view
*/

int			get_sound_dir(t_trantorian src, t_trantorian dst, t_map map)
{
	int			x;
	int			y;
	t_sound_dir horizontal;
	t_sound_dir vertical;

	x = ft_abs(dst.pos_x - src.pos_x);
	y = ft_abs(dst.pos_y - src.pos_y);
	horizontal = sound_x(src, dst, map, x);
	vertical = sound_y(src, dst, map, y);
	return (sound_direction(horizontal, vertical, dst.direction));
}
