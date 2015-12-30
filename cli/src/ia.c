/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 22:35:26 by flime             #+#    #+#             */
/*   Updated: 2015/12/24 22:29:55 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "general.h"
#include "client.h"

void ia(t_env *env)
{
	if (env->status == status_avance)
		cmd(env, CMD_AVANCE, "");
	else if (env->status == status_droite)
		cmd(env, CMD_DROITE, "");
	else if (env->status == status_gauche)
		cmd(env, CMD_GAUCHE, "");
	else if (env->status == status_voir)
		cmd(env, CMD_VOIR, "");
	else if (env->status == status_inventaire)
		cmd(env, CMD_INVENTAIRE, "");
	else if (env->status == status_prend)
		cmd(env, CMD_PREND, " 0");
	else if (env->status == status_pose)
		cmd(env, CMD_POSE, " 0");
	// else if (env->status == status_expulse) //manque le retour ok???
	// 	cmd(env, CMD_EXPULSE, "");
	else if (env->status == status_broadcast)
		cmd(env, CMD_BROADCAST, " Je suis là");
	else if (env->status == status_incantation)
		cmd(env, CMD_INCANTATION, "");
	else if (env->status == status_fork)
		cmd(env, CMD_FORK, "");
	else if (env->status == status_connect_nbr)
		cmd(env, CMD_CONNECT_NBR, "");
}

// void ia(t_env *env)
// {
// 	if (env->status == status_avance)
// 	{
// 		cmd(env, CMD_VOIR, "");
// 		// cmd(env, CMD_AVANCE, "");
// 		// cmd(env, CMD_INCANTATION, "");
// 		cmd(env, CMD_VOIR, "");
// 		// cmd(env, CMD_VOIR, "");
// 	}
	
// 	// else if (env->status == status_droite)
// 	// 	cmd(env, CMD_DROITE, "");
// 	// else if (env->status == status_gauche)
// 	// 	cmd(env, CMD_GAUCHE, "");
// 	// else if (env->status == status_voir)
// 	// 	cmd(env, CMD_VOIR, "");
// 	// else if (env->status == status_inventaire)
// 	// 	cmd(env, CMD_INVENTAIRE, "");
// 	// else if (env->status == status_prend)
// 	// 	cmd(env, CMD_PREND, " 0");
// 	// else if (env->status == status_pose)
// 	// 	cmd(env, CMD_POSE, " 0");
// 	// // else if (env->status == status_expulse) //manque le retour ok???
// 	// // 	cmd(env, CMD_EXPULSE, "");
// 	// else if (env->status == status_broadcast)
// 	// 	cmd(env, CMD_BROADCAST, " Je suis là");
// 	// else if (env->status == status_incantation)
// 	// 	cmd(env, CMD_INCANTATION, "");
// 	// else if (env->status == status_fork)
// 	// 	cmd(env, CMD_FORK, "");
// 	// else if (env->status == status_connect_nbr)
// 	// 	cmd(env, CMD_CONNECT_NBR, "");
// }
