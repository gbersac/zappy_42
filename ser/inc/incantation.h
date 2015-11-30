/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incantation.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 21:37:32 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/11 21:02:44 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCANTATION_H
# define INCANTATION_H

#include <stdlib.h>

# include "list.h"
# include "libft.h"

# define NB_LEVEL	8

typedef struct	s_incantation
{
	int		beg_level;
	int		end_level;
	int		players;
	int		nb_linemate;
	int		nb_deraumere;
	int		nb_sibur;
	int		nb_mendiane;
	int		nb_phiras;
	int		nb_thystame;
}				t_incantation;

t_incantation	*get_lst_lvl(void);

#endif
