/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_incantation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/08 12:59:15 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

static t_list	*get_lst_trantor(t_env *env, t_trantorian *trantor, int n_play)
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
 				env->fds[i].trantor.level == trantor->level &&
 				strcmp(env->fds[i].trantor.team, trantor->team) == 0)
		{
			ft_listpushback(&lst, &env->fds[i]);
			if (ft_listcnt(lst) == n_play)
				return (lst);
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
	return (1);
}

/*
** up each level trantor and countdown.
*/
static void		modify_trantor(t_env *env,
		t_list *trantors,
		t_trantorian *initiator,
		t_incantation *incant)
{
	t_fd			*fd;
	t_list			*iter;

	iter = trantors;
	sub_inventory(&initiator->inventory, &incant->required_resources);
	while (iter != NULL)
	{
		fd = (t_fd*) iter->data;
		fd->trantor.level += 1;
		/* the initiator will have its countdown increased at the end */
		if (fd->trantor.id != initiator->id)
		{
			fd->trantor.countdown += CMD_INCANTATION_TIME;
			send_cmd_to_client(&env->fds[fd->trantor.id], "incantation");
		}
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
		printf("incantation %d failed because not enough players\n",
				trantor->level);
		send_cmd_to_client(fd, MSG_KO);
		return (-1);
	}
	if (!trantor_has_resources(trantor, incant))
	{
		printf("incantation %d failed because not enough resources\n",
				trantor->level);
		send_cmd_to_client(fd, MSG_KO);
		return (-1);
	}
	return (0);
}

int				ser_incantation(t_env *env, t_fd *fd, char *cmd)
{
	t_square		*sq;
	t_trantorian	*trantor;
	t_list			*trantors_fd;
	t_incantation	incant;

	trantor = &fd->trantor;
	sq = get_square(env, trantor->pos_x, trantor->pos_y);
	incant = incantation_to_evolve(trantor->level);
	trantors_fd = get_lst_trantor(env, trantor, incant.players);
	if (test_incantation_feasability(trantor, &incant, fd, trantors_fd) == -1)
		return (-1);
	printf("new incantation for level %d\n", incant.beg_level);
	modify_trantor(env, trantors_fd, trantor, &incant);
	test_for_victory(env);
	gfx_pic(env, trantors_fd);
	return (0);
	(void)cmd;
}
