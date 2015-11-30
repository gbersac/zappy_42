/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 23:59:17 by rfrey             #+#    #+#             */
/*   Updated: 2014/06/11 20:44:12 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "gfx.h"
#include "general.h"

void	init_env(t_env *env)
{
	ft_bzero(env, sizeof(t_env));
	env->hostname = "127.0.0.1";
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
