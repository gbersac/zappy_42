/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeday.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 19:29:37 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 21:07:34 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

long long	get_time_now(void)
{
	struct timeval	tv;
	time_t			curtime;
	long long		to_return;

	gettimeofday(&tv, NULL);
	curtime = tv.tv_sec * 1000 + tv.tv_usec;
	return (curtime);
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
