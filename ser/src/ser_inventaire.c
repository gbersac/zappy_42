/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_inventaire.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/11 21:06:30 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

static int	nb_res_inventory(t_resource res, t_list *inventory)
{
	int				nb;
	t_resource		r;

	nb = 0;
	while (inventory != NULL)
	{
		r = *((t_resource*)inventory->data);
		if (res == r)
			++nb;
		inventory = inventory->next;
	}
	return (nb);
}

static void	append_res_str(char **prev, char *label, int nb)
{
	char	str[1024];

	sprintf(str, "%s%s %d, ", *prev, label, nb);
	free(*prev);
	*prev = strdup(str);
}

static void	end_ser_inventaire(char *str, t_fd *fd)
{
	char			*buf;

	buf = str;
	str = (char*)malloc(sizeof(char) * strlen(str) + 5);
	memcpy(str, buf, strlen(buf) + 1);
	strcat(str, "}");
	ft_listpushback(&fd->to_send, str);
}

int			ser_inventaire(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;
	t_list			*lst_res;
	t_resource_lst	*r;
	char			*str;
	int				nb_res;

	lst_res = get_lst_resource();
	trantor = &(fd->trantor);
	str = strdup("{");
	while (lst_res != NULL)
	{
		r = (t_resource_lst*)lst_res->data;
		nb_res = nb_res_inventory(r->type, trantor->inventory);
		if (nb_res != 0)
			append_res_str(&str, r->label, nb_res);
		lst_res = lst_res->next;
	}
	end_ser_inventaire(str, fd);
	env = NULL;
	cmd = NULL;
	return (0);
}
