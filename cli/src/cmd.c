/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 23:15:24 by flime             #+#    #+#             */
/*   Updated: 2015/12/24 21:48:21 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.h"
#include "../../libft/inc/libft.h"

void	cmd(t_env *env, char *cmd, char *str)
{
	char	*ret;

	if (str)
		ret = ft_strjoin(cmd, str);
	else
		ret = cmd;
	ft_listpushback(&env->buf_write, ret);
}