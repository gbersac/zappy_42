/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 16:52:36 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/02 21:51:22 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

char		*square_to_str(t_env *env, int x, int y)
{
	t_square	*sq;
	t_list		*iter;

	sq = get_square(env, x, y);
	iter= sq->content;
	return (resources_to_str(iter));
}
