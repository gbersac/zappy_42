/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incantation.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 21:37:32 by gbersac           #+#    #+#             */
/*   Updated: 2015/12/05 19:13:04 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCANTATION_H
# define INCANTATION_H

# include <stdlib.h>

# include "list.h"
# include "general.h"
# include "libft.h"

# define NB_LEVEL			8

/*
** Number of trantor required to reach max level.
*/
# define NB_TRANTOR_VICTORY	6

/*
** The number of inactive client turns
** (turns after the server send an `ok` message) before resending an `relaunch`
** message to trigger a client response.
*/
# define NB_TURN_BEFORE_TRANTOR_CALLBACK	350

/*
** This structure represent the ressources required to launch an incantation.
*/
typedef struct	s_incantation
{
	int		beg_level;
	int		end_level;

	/*
	** The number of players required to create an incantation.
	*/
	int		players;

	t_inventory	required_resources;
}				t_incantation;

t_incantation	*get_lst_lvl(void);

/*
** Return the incantation needed to eveolve for a trantorian of level `level`.
*/
t_incantation	incantation_to_evolve(int level);

#endif
