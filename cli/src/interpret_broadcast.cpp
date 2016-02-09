/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_broadcast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 08:18:17 by flime             #+#    #+#             */
/*   Updated: 2015/12/30 08:18:20 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "general.h"
#include "client.hpp"

void		interpret_broadcast(t_env *env, char *get)
{
	char **split;

	split = ft_strsplit(get, ',');
	(void)env;
	(void)get;
	ft_putstr("interpret_broadcast");
	ft_strtabput(split);
	if (!ft_strcmp(split[3], "BONJOUR"))
		ft_putendl("BONJOUR");
	else if (!ft_strcmp(split[3], "INVENTAIRE"))
	{
		ft_putendl("INVENTAIRE");
		ft_putendl(split[4]);
	}
	else if (!ft_strcmp(split[3], "REUNION"))
		ft_putendl("REUNION");
	else if (!ft_strcmp(split[3], "BESOIN"))
		ft_putendl("BESOIN");
	else if (!ft_strcmp(split[3], "GRADE_UP"))
	{
		ft_putendl("GRADE_UP");
		env->n_client++;
		ft_putstr("grade: ");
		ft_putnbr(env->n_client);
		ft_putendl("");
	}
}
