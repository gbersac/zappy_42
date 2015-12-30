/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 06:02:44 by flime             #+#    #+#             */
/*   Updated: 2015/12/30 06:02:47 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "general.h"
#include "client.h"

void		play(t_env *env)
{
	char	*get;

	get = (char*)ft_listpop(&env->buf_read);
	ft_putstr("\e[0;31m[server]: \e[0m");
	ft_putendl(get);
	interpret_msg(env, get);
	ia(env);
	free(get);
}
