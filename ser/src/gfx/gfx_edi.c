/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_edi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 14:14:15 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 20:54:21 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	gfx_edi(t_env *env)
{
	char	*to_send;

	to_send = (char*)malloc(4);
	memcpy(to_send, "edi ", 4);
	send_cmd_to_graphics(env, to_send);
	return (1);
}
