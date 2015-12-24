/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_voir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/24 23:19:50 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd.h"

static void	add_sq_str(t_env *env, int x, int y, char **prev)
{
	char	*str;
	char	*buf;

	if (*prev == NULL)
	{
		*prev = (char*)malloc(sizeof(char) * 5);
		bzero(*prev, 5);
		*prev[0] = '{';
	}
	str = inventory_to_str(&get_square(env, x, y)->content);
	buf = *prev;
	*prev = (char*)malloc(strlen(str) + strlen(buf) + 3);
	sprintf(*prev, "%s%s, ", buf, str);
	free(buf);
}

static char	*explore_vert(t_env *env, t_fd *fd, int inc)
{
	int				x;
	int				y;
	char			*to_return;
	t_trantorian	*t;

	t = &fd->trantor;
	to_return = NULL;
	y = 0;
	while (y <= t->level)
	{
		x = -y + t->pos_x;
		while (x <= y)
		{
			add_sq_str(env, t->pos_x + x, t->pos_y + y, &to_return);
			++x;
		}
		y += inc;
	}
	return (to_return);
}

static char	*explore_hori(t_env *env, t_fd *fd, int inc)
{
	int		x;
	int		y;
	char	*to_return;
	t_trantorian	*t;

	x = 0;
	t = &fd->trantor;
	to_return = NULL;
	while (x < t->level)
	{
		y = -x;
		while (y <= x)
		{
			add_sq_str(env, t->pos_x + x, t->pos_y + y, &to_return);
			++y;
		}
		x += inc;
	}
	return (to_return);
}

static void	end_ser_voir(t_fd *fd, char *str)
{
	char			*buf;
	char *ret;

	buf = str;
	str = (char*)malloc(sizeof(char) * strlen(str) + 3);
	memcpy(str, buf, strlen(buf) + 1);
	ret = ft_strsub(str, 0, strlen(buf) - 2);
	strcat(ret, "}");
	send_cmd_to_client(fd, ret);
}

int			ser_voir(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;
	char			*str;

	trantor = &(fd->trantor);
	switch (trantor->direction)
	{
		case LEFT:
			str = explore_hori(env, fd, -1);
			break ;
		case RIGHT:
			str = explore_hori(env, fd, +1);
			break ;
		case UP:
			str = explore_vert(env, fd, -1);
			break ;
		case DOWN:
			str = explore_vert(env, fd, +1);
			break ;
	}
	end_ser_voir(fd, str);
	cmd = NULL;
	return (0);
}
