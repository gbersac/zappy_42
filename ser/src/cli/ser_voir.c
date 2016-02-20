/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_voir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2016/02/20 21:26:45 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void	add_sq_str(t_env *env, int x, int y, char **prev)
{
	char	*str;
	char	*buf;

	if (*prev == NULL)
		*prev = strdup("voir {");
	str = inventory_to_str(&get_square(env, x, y)->content);
	buf = *prev;
	asprintf(prev, "%s%s, ", buf, str);
	free(buf);
}

static char	*explore_vert(t_env *env, t_fd *fd, int inc)
{
	int				x;
	int				y;
	int				lv;
	char			*to_return;
	t_trantorian	*t;

	t = &fd->trantor;
	to_return = NULL;
	lv = 0;
	while (lv <= t->level)
	{
		y = lv * inc;
		x = (y > 0) ? (y * -1) : y;
		while (x <= lv)
		{
			add_sq_str(env, t->pos_x + x, t->pos_y + y, &to_return);
			++x;
		}
		++lv;
	}
	return (to_return);
}

static char	*explore_hori(t_env *env, t_fd *fd, int inc)
{
	int				x;
	int				y;
	int				lv;
	char			*to_return;
	t_trantorian	*t;

	t = &fd->trantor;
	to_return = NULL;
	lv = 0;
	while (lv <= t->level)
	{
		x = lv * inc;
		y = (x > 0) ? (x * -1) : x;
		while (y <= lv)
		{
			add_sq_str(env, t->pos_x + x, t->pos_y + y, &to_return);
			y++;
		}
		lv++;
	}
	return (to_return);
}

static void	end_ser_voir(t_env *env, t_fd *fd, char *str)
{
	char	*ret;

	str[strlen(str) - 2] = '\0';
	asprintf(&ret, "%s}", str);
	send_cmd_to_client(fd, ret);
	free(ret);
	(void)env;
}

int			ser_voir(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;
	char			*str;

	trantor = &(fd->trantor);
	str = NULL;
	if (trantor->direction == NORTH)
		str = explore_vert(env, fd, +1);
	else if (trantor->direction == EAST)
		str = explore_hori(env, fd, +1);
	else if (trantor->direction == SOUTH)
		str = explore_vert(env, fd, -1);
	else if (trantor->direction == WEST)
		str = explore_hori(env, fd, -1);
	else
		return (-1);
	end_ser_voir(env, fd, str);
	return (0);
	(void)cmd;
}
