/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_bct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 19:34:39 by gbersac           #+#    #+#             */
/*   Updated: 2016/01/06 18:00:07 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

char	*gfx_bct_str(t_env *env, int x, int y)
{
	t_square	*sq;
	char		*to_send;
	char		*inventory_str;

	sq = get_square(env, x, y);
	inventory_str = inventory_to_str(&sq->content);
	asprintf(&to_send, "bct %d %d %s",
			x, y,
			inventory_str);
	return (to_send);
}

int		gfx_bct_call(t_env *env, t_fd *fd, int x, int y)
{
	char		*to_send;

	t_inventory	*inventory;
	t_square	*sq;

	sq = get_square(env, x, y);
	inventory = &sq->content;
	asprintf(&to_send, "bct %d %d %d %d %d %d %d %d %d", x, y,
			nb_res_in_inventory(inventory, FOOD),
			nb_res_in_inventory(inventory, LINEMATE),
			nb_res_in_inventory(inventory, DERAUMERE),
			nb_res_in_inventory(inventory, SIBUR),
			nb_res_in_inventory(inventory, MENDIANE),
			nb_res_in_inventory(inventory, PHIRAS),
			nb_res_in_inventory(inventory, THYSTAME));
	printf("\e[0;31mto->[gfx]\e[0m %s\n", to_send);
	send_cmd_to_client(fd, to_send);
	return (1);
}

int		gfx_bct(t_env *env, t_fd *fd, char *cmd)
{
	int		x;
	int		y;

	sscanf(cmd, "bct %d %d\n", &x, &y);
	gfx_bct_call(env, fd, x, y);
	return (1);
}
