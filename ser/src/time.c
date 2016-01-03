/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 19:29:37 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/06 20:48:21 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

long long	get_time_now(void)
{
	struct timeb	tp;
	int				res;
	long long		to_return;

	res = ftime(&tp);
	to_return = 1000.0 * tp.time + tp.millitm;
	return (to_return);
}

int			is_new_turn(t_env *env)
{
	static long long	last = 0;
	long long			elapsed;
	long long			now;

	now = get_time_now();
	if (last == 0)
		last = now;
	elapsed = now - last;
	if (elapsed > (long long)(1000.0 / env->map.time_d))
	{
		last = now;
		return (1);
	}
	return (0);
}
