/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ser_voir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/08 15:31:59 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/05 19:00:22 by gbersac          ###   ########.fr       */
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
	printf("vertival trantorpos (%d,%d) orientation %d\n", t->pos_x, t->pos_y, inc);
	while (y <= t->level)
	{
		x = -y;
		while (x <= y)
		{
			printf("\tregard pos (%d,%d)\n", t->pos_x + x, t->pos_y + y);
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
	printf("horizontal trantorpos (%d,%d) orientation %d\n", t->pos_x, t->pos_y, inc);
	while (x < t->level)
	{
		y = -x;
		while (y <= x)
		{
			printf("\tregard pos (%d,%d)\n", t->pos_x + x, t->pos_y + y);
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
	printf("\e[0;33mto->[client_%d]\e[0m %s\n", fd->fd, ret);
	send_cmd_to_client(fd, ret);
}

int			ser_voir(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;
	char			*str;

	trantor = &(fd->trantor);
	switch (trantor->direction)
	{
		case NORTH:
			str = explore_vert(env, fd, +1);
			break ;
		case EAST:
			str = explore_hori(env, fd, +1);
			break ;
		case SOUTH:
			str = explore_vert(env, fd, -1);
			break ;
		case WEST:
			str = explore_hori(env, fd, -1);
			break ;
		default:
			return (0);
			break;
	}
	end_ser_voir(fd, str);
	cmd = NULL;
	return (0);
}
