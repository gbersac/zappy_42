/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_the_king.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 13:40:30 by flime             #+#    #+#             */
/*   Updated: 2015/12/24 00:22:46 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../gen/inc/general.h"
// #include "../../ser/inc/map.h"
#include <stdio.h>

// typedef enum	e_direction
// {
// 	UP,
// 	RIGHT,
// 	DOWN,
// 	LEFT
// }				t_direction;

// typedef enum	e_sound_dir
// {
// 	U,
// 	R,
// 	D,
// 	L,
// 	C
// }				t_sound_dir;

// typedef struct	s_map
// {
// 	int			width;
// 	int			height;
// 	// t_list		*teams;
// 	// int			time_d;
// 	// int			max_client;

// 	/*
// 	** Pointer to the table of square which is the map. Case numerotation is :
// 	** 0 1 2
// 	** 3 4 5...
// 	*/
// 	// t_square	*tartan;
// }				t_map;

// typedef struct	s_trantorian
// {
// 	// int			health_point;
// 	int			pos_x;
// 	int			pos_y;
// 	// t_list		*inventory;
// 	// int			level;
// 	t_direction	direction;

// 	/*
// 	** Time before the trantor is allow to do something.
// 	*/
// 	// int			countdown;
// }				t_trantorian;

// /*
// ** Sound direction starts from trantorian sight 1
// ** and rotates anticlockwise
// */

// int			ft_abs(int n)
// {
// 	return ((n < 0) ? -n : n);
// }

// static int	sound_direction(t_sound_dir h, t_sound_dir v, t_direction d)
// {
// 	if (h == C && v == C)
// 		return (0);
// 	else if (h == C && v == U)
// 		return (1 + d * 2);
// 	else if (h == L && v == U)
// 		return (2 + d * 2);
// 	else if (h == L && v == C)
// 		return (3 + d * 2) % 8;
// 	else if (h == L && v == D)
// 		return (4 + d * 2) % 8;
// 	else if (h == C && v == D)
// 		return (5 + d * 2) % 8;
// 	else if (h == R && v == D)
// 		return (6 + d * 2) % 8;
// 	else if (h == R && v == C)
// 		return (7 + d * 2) % 8;
// 	else if (h == R && v == U)
// 		return (8 + d * 2) % 8;
// 	return (-1);
// }

// static int	sound_x(t_trantorian src, t_trantorian dst, t_map m, t_sound_dir x)
// {
// 	if ((int)(x + x) > m.width)
// 	{
// 		if (src.pos_x < dst.pos_x)
// 		{
// 			x = src.pos_x + m.width - dst.pos_x;
// 			return (R);
// 		}
// 		else if (src.pos_x > dst.pos_x)
// 		{
// 			x = dst.pos_x + m.width - src.pos_x;
// 			return (L);
// 		}
// 		else
// 			return (C);
// 	}
// 	else
// 	{
// 		if (src.pos_x < dst.pos_x)
// 			return (L);
// 		else if (src.pos_x > dst.pos_x)
// 			return (R);
// 		else
// 			return (C);
// 	}
// }

// static int	sound_y(t_trantorian src, t_trantorian dst, t_map m, t_sound_dir y)
// {
// 	if ((int)(y + y) > m.height)
// 	{
// 		if (src.pos_y < dst.pos_y)
// 		{
// 			return (U);
// 			y = src.pos_y + m.width - dst.pos_y;
// 		}
// 		else if (src.pos_y > dst.pos_y)
// 		{
// 			return (D);
// 			y = dst.pos_y + m.width - src.pos_y;
// 		}
// 		else
// 			return (C);
// 	}
// 	else
// 	{
// 		if (src.pos_y < dst.pos_y)
// 			return (D);
// 		else if (src.pos_y > dst.pos_y)
// 			return (U);
// 		else
// 			return (C);
// 	}
// }

/*
** find source sound direction from dst point of view
*/

// int			get_sound_dir(t_trantorian src, t_trantorian dst, t_map map)
// {
// 	int			x;
// 	int			y;
// 	t_sound_dir horizontal;
// 	t_sound_dir vertical;

// 	x = ft_abs(dst.pos_x - src.pos_x);
// 	y = ft_abs(dst.pos_y - src.pos_y);
// 	horizontal = sound_x(src, dst, map, x);
// 	vertical = sound_y(src, dst, map, y);
// 	return (sound_direction(horizontal, vertical, dst.direction));
// }


void		join_the_king(int sound_dir)
{
	if (ret == 2 || ret == 1 || ret == 8)
		printf("MOVE");// move
	else if (ret == 7 || ret == 6|| ret == 5)
		printf("ROT DROITE");
	else
		printf("ROT GAUCHE");
}


// int main(void)
// {
// 	t_map			map;
// 	t_trantorian	king;
// 	t_trantorian	subject;
// 	int				ret;

// 	map.width = 10;
// 	map.height = 10;
// 	king.pos_x = 2;
// 	king.pos_y = 7;
// 	king.direction = UP;
// 	subject.pos_x = 5;
// 	subject.pos_y = 2;
// 	subject.direction = RIGHT;

// 	while ((ret = get_sound_dir(king, subject, map)))
// 	{
// 		if (ret == 2 || ret == 1 || ret == 8)
// 			printf("MOVE");// move
// 		else if (ret == 7 || ret == 6|| ret == 5)
// 		{
// 			printf("ROT DROITE");
// 		}
// 		else
// 		{
// 			printf("ROT GAUCHE");
// 		}
// 		printf("%d\n", ret);
// 		break ;
// 	}
// 	return (0);
// }