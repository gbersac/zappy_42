/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 22:35:26 by flime             #+#    #+#             */
/*   Updated: 2016/01/18 20:38:45 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "general.h"
#include "client.h"

// void ia(t_env *env)
// {
// 	if (env->status == status_avance)
// 		cmd(env, CMD_AVANCE, "");
// 	else if (env->status == status_droite)
// 		cmd(env, CMD_DROITE, "");
// 	else if (env->status == status_gauche)
// 		cmd(env, CMD_GAUCHE, "");
// 	else if (env->status == status_voir)
// 		cmd(env, CMD_VOIR, "");
// 	else if (env->status == status_inventaire)
// 		cmd(env, CMD_INVENTAIRE, "");
// 	else if (env->status == status_prend)
// 		cmd(env, CMD_PREND, " linemate");
// 	else if (env->status == status_pose)
// 		cmd(env, CMD_POSE, " linemate");
// 	// else if (env->status == status_expulse) //manque le retour ok???
// 	// 	cmd(env, CMD_EXPULSE, "");
// 	else if (env->status == status_broadcast_bonjour)
// 		broadcast_bonjour(env);
// 	else if (env->status == status_broadcast_inventaire)
// 		broadcast_inventaire(env);
// 	else if (env->status == status_broadcast_reunion)
// 		broadcast_reunion(env);
// 	else if (env->status == status_broadcast_besoin)
// 		broadcast_besoin(env);
// 	else if (env->status == status_broadcast_grade_up)
// 		broadcast_grade_up(env);
// 	else if (env->status == status_incantation)
// 		cmd(env, CMD_INCANTATION, "");
// 	else if (env->status == status_fork)
// 		cmd(env, CMD_FORK, "");
// 	else if (env->status == status_connect_nbr)
// 		cmd(env, CMD_CONNECT_NBR, "");
// }

void ia(t_env *env)
{
	printf("IA\n");
	// if (env->status == status_welcome)
	// 	cmd(env, "PLAYER", "");
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
		cmd(env, CMD_PREND, " linemate");
	else if (env->status == status_pose)
		cmd(env, CMD_POSE, " linemate");
	// else if (env->status == status_expulse) //manque le retour ok???
	// 	cmd(env, CMD_EXPULSE, "");
	else if (env->status == status_broadcast_bonjour)
		broadcast_bonjour(env);
	else if (env->status == status_broadcast_inventaire)
		broadcast_inventaire(env);
	else if (env->status == status_broadcast_reunion)
		broadcast_reunion(env);
	else if (env->status == status_broadcast_besoin)
		broadcast_besoin(env);
	else if (env->status == status_broadcast_grade_up)
		broadcast_grade_up(env);
	else if (env->status == status_incantation)
		cmd(env, CMD_INCANTATION, "");
	else if (env->status == status_fork)
		cmd(env, CMD_FORK, "");
	else if (env->status == status_connect_nbr)
		cmd(env, CMD_CONNECT_NBR, "");
}

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
