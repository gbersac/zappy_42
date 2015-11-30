/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 22:36:03 by rfrey             #+#    #+#             */
/*   Updated: 2014/06/11 21:12:58 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void		alc(t_list **lst, char *label, t_cmd_fct fct, int t)
{
	t_cmd	*newc;

	newc = (t_cmd*)malloc(sizeof(t_cmd));
	newc->label = label;
	newc->fct = fct;
	newc->time = t;
	ft_listpushback(lst, newc);
}

static t_list	*get_lst_cmd(void)
{
	static t_list	*lst = NULL;

	if (lst == NULL)
	{
		alc(&lst, CMD_AVANCE, ser_avance, CMD_AVANCE_TIME);
		alc(&lst, CMD_DROITE, ser_droite, CMD_DROITE_TIME);
		alc(&lst, CMD_GAUCHE, ser_gauche, CMD_GAUCHE_TIME);
		alc(&lst, CMD_VOIR, ser_voir, CMD_VOIR_TIME);
		alc(&lst, CMD_INVENTAIRE, ser_inventaire, CMD_INVENTAIRE_TIME);
		alc(&lst, CMD_PREND, ser_prend, CMD_PREND_TIME);
		alc(&lst, CMD_POSE, ser_pose, CMD_POSE_TIME);
		alc(&lst, CMD_EXPULSE, ser_expulse, CMD_EXPULSE_TIME);
		alc(&lst, CMD_BROADCAST, ser_broadcast, CMD_BROADCAST_TIME);
		alc(&lst, CMD_INCANTATION, ser_incantation, CMD_INCANTATION_TIME);
		alc(&lst, CMD_FORK, ser_fork, CMD_FORK_TIME);
		alc(&lst, CMD_CONNECT_NBR, ser_connect_nbr, CMD_CONNECT_NBR_TIME);
	}
	return (lst);
}

int				interpret_cmd(t_env *e, t_fd *fd, char *cmd)
{
	t_list	*lst_cmd;
	int		res;
	t_cmd	*command;

	if (fd->trantor.countdown > 0)
	{
		ft_listpushback(&fd->to_send, strdup(MSG_KO));
		return (0);
	}
	lst_cmd = get_lst_cmd();
	while (lst_cmd != NULL)
	{
		command = lst_cmd->data;
		if (ft_strnequ(command->label, cmd, strlen(command->label)))
		{
			res = command->fct(e, fd, cmd);
			if (res >= 0)
				fd->trantor.countdown = command->time;
			break ;
		}
		lst_cmd = lst_cmd->next;
	}
	return (0);
}
