/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 23:59:17 by flime             #+#    #+#             */
/*   Updated: 2014/06/05 00:03:52 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "general.h"
#include "client.h"

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
