/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_voir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 23:17:00 by flime             #+#    #+#             */
/*   Updated: 2015/12/24 22:56:24 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include "../inc/client.h"

void	parse_voir(t_env *env, char *str)
{
	char	*without_bracket;
	char	**astr;
	char	**case_astr;
	int		i;

	(void)env;

	ft_putendl("parse_voir()");

	// ft_putendl(str);
	without_bracket = ft_strsub(str, 1, ft_strlen(str) - 2);
	// ft_putendl(without_bracket);
	astr = ft_strsplit(without_bracket, ',');
	// ft_strtabput(astr);
	i = 0;
	// while (astr[i])
	// {
		case_astr = ft_strsplit(astr[i], ' ');
		// ft_strtabput(case_astr);
		// i++;
	// }
	i = 0;
	// while (case_astr[i])
	// {
		// cmd(env, "prend ", "1 0 0 0 0 0 0");
	// 	i++;
	// }
	// env->status = voir;
	// cmd(env, "voir", NULL);// test a delete
}