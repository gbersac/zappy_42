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
	// printf("%lld\n", to_return);
	return (to_return);
}

int					get_num_turn(t_env *env)
{
	static long long	begin = 0;
	long long			elapsed;
	int					to_return;

	if (begin == 0)
		begin = get_time_now();
	elapsed = get_time_now() - begin;
	to_return = elapsed * env->map.time_d / 1000.0;
	// printf("calc num turn %lld / %lld\n", elapsed, (long long) (env->map.time_d * 1000.0));
	return (to_return);
}
