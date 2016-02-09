/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 23:15:24 by flime             #+#    #+#             */
/*   Updated: 2016/01/06 14:27:19 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

/*
** str: must not end with a '\n'
** Guillaume: when you send a cmd, end it with a '\n'
*/
void	cmd(t_env *env, const char *cmd, const char *str)
{
	char	*ret;

	if (str)
		asprintf(&ret, "%s %s\n", cmd, str);
	else
		asprintf(&ret, "%s\n", cmd);
	ft_listpushback(&env->buf_write, ret);
}
