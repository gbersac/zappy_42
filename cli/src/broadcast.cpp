/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 12:08:50 by flime             #+#    #+#             */
/*   Updated: 2015/12/30 12:08:52 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <unistd.h>
// #include "libft.h"
// #include "general.h"
// #include "client.hpp"
//
// char *broadcast_from(t_env *env)
// {
// 	char *str;
//
// 	str = ft_strjoin(" ,", ft_itoa(env->n_client));
// 	str = ft_strjoin(str, ",");
// 	str = ft_strjoin(str, env->trantor.team);
// 	str = ft_strjoin(str, ",");
// 	return (str);
// }
//
// // void broadcast_bonjour(t_env *env)
// // {
// // 	cmd(env, CMD_BROADCAST, ft_strjoin(broadcast_from(env), "BONJOUR"));
// // }
//
// void broadcast_inventaire(t_env *env)
// {
// 	char *str;
//
// 	str = ft_strjoin("INVENTAIRE,", inventory_to_str(&env->inventory));
// 	cmd(env, CMD_BROADCAST, ft_strjoin(broadcast_from(env), str));
// }
//
// void broadcast_reunion(t_env *env)
// {
// 	cmd(env, CMD_BROADCAST, ft_strjoin(broadcast_from(env), "REUNION"));
// }
//
// void broadcast_besoin(t_env *env)
// {
// 	cmd(env, CMD_BROADCAST, ft_strjoin(broadcast_from(env), "BESOIN"));
// }
//
// #<{(|
// ** Demande a tous d'augmenter en grade (nb_client)
// |)}>#
//
// void broadcast_grade_up(t_env *env)
// {
// 	cmd(env, CMD_BROADCAST, ft_strjoin(broadcast_from(env), "GRADE_UP"));
// 	env->n_client++;
// 	ft_putstr("grade: ");
// 	ft_putnbr(env->n_client);
// 	ft_putendl("");
// }
