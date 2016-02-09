/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 23:59:17 by rfrey             #+#    #+#             */
/*   Updated: 2014/06/05 00:03:52 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <stdlib.h>
	#include "libft.h"
	#include "general.h"
}

#include "client.hpp"

void	init_env(t_env *env)
{
	ft_bzero(env, sizeof(t_env));
	env->hostname = strdup("127.0.0.1");
}

void	free_env(t_env *env)
{
	char	*tmp;

	while (env->buf_read)
	{
		tmp = (char*)ft_listpop(&env->buf_read);
		free(tmp);
	}
	while (env->buf_write)
	{
		tmp = (char*)ft_listpop(&env->buf_write);
		free(tmp);
	}
}
