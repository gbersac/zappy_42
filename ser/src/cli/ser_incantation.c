/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_incantation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/19 19:09:08 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

static t_list	*get_lst_trantor(t_env *env, t_trantorian *trantor)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = NULL;
	while (i < env->maxfd)
	{
		if (env->fds[i].type == FD_CLIENT &&
				env->fds[i].trantor.pos_x == trantor->pos_x &&
				env->fds[i].trantor.pos_y == trantor->pos_y &&
				env->fds[i].trantor.level == trantor->level)
		{
			ft_listpushback(&lst, &env->fds[i]);
		}
		++i;
	}
	return (lst);
}

static int		trantor_has_resources(t_trantorian *trantor,
		t_incantation *incant)
{
	t_inventory	reqres;

	reqres = incant->required_resources;
	if (trantor->inventory.nb_linemate < reqres.nb_linemate)
		return (0);
	if (trantor->inventory.nb_deraumere < reqres.nb_deraumere)
		return (0);
	if (trantor->inventory.nb_sibur < reqres.nb_sibur)
		return (0);
	if (trantor->inventory.nb_mendiane < reqres.nb_mendiane)
		return (0);
	if (trantor->inventory.nb_phiras < reqres.nb_phiras)
		return (0);
	if (trantor->inventory.nb_thystame < reqres.nb_thystame)
		return (0);
	trantor->inventory.nb_linemate -= reqres.nb_linemate;
	trantor->inventory.nb_deraumere -= reqres.nb_deraumere;
	trantor->inventory.nb_sibur -= reqres.nb_sibur;
	trantor->inventory.nb_mendiane -= reqres.nb_mendiane;
	trantor->inventory.nb_phiras -= reqres.nb_phiras;
	trantor->inventory.nb_thystame -= reqres.nb_thystame;
	return (1);
}

/*
** up each level trantor and countdown.
*/
static void		modify_trantor(t_list *trantors, t_trantorian *initiator)
{
	t_trantorian	*trantor;
	t_list			*iter;

	iter = trantors;
	while (iter != NULL)
	{
		trantor = (t_trantorian*) iter->data;
		trantor->level += 1;
		/* the initiator will have its countdown increased at the end */
		if (trantor->id != initiator->id)
			trantor->countdown += CMD_INCANTATION_TIME;
		iter = iter->next;
	}
}

static int		test_incantation_feasability(t_trantorian *trantor,
		t_incantation *incant,
		t_fd *fd,
		t_list *trantors)
{
	if (ft_listcnt(trantors) < incant->players)
	{
		printf("incantation failed because not enough players\n");
		send_cmd_to_client(fd, MSG_KO);
		return (-1);
	}
	if (!trantor_has_resources(trantor, incant))
	{
		printf("incantation faile because not enough resources\n");
		send_cmd_to_client(fd, MSG_KO);
		return (-1);
	}
	return (0);
}

int				ser_incantation(t_env *env, t_fd *fd, char *cmd)
{
	t_square		*sq;
	t_trantorian	*trantor;
	t_list			*trantors;
	t_incantation	incant;

	trantor = &fd->trantor;
	sq = get_square(env, trantor->pos_x, trantor->pos_y);
	trantors = get_lst_trantor(env, trantor);
	incant = incantation_to_evolve(trantor->level);
	if (test_incantation_feasability(trantor, &incant, fd, trantors) == -1)
		return (-1);
	printf("new incantation for level %d\n", incant.big_level);
	modify_trantor(trantors, trantor);
	send_cmd_to_client(fd, MSG_OK);
	test_for_victory(env);
	return (0);
	cmd = NULL;
}
