/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 23:00:10 by gbersac           #+#    #+#             */
/*   Updated: 2014/06/04 23:30:57 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_ENV_H
# define UPDATE_ENV_H

# include "bircd.h"

int		update_width(t_env *e, char **av);
int		update_height(t_env *e, char **av);
int		update_teams(t_env *e, char **av);
int		update_nb(t_env *e, char **av);
int		update_time(t_env *e, char **av);

#endif
