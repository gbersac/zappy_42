/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_inventaire.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 23:17:05 by flime             #+#    #+#             */
/*   Updated: 2015/12/24 00:23:16 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include "../inc/client.h"

void print_inventaire(t_env *env)
{
	ft_putendl("");ft_putnbr(env->inventory.nb_food);
	ft_putendl("");ft_putnbr(env->inventory.nb_linemate);
	ft_putendl("");ft_putnbr(env->inventory.nb_deraumere);
	ft_putendl("");ft_putnbr(env->inventory.nb_sibur);
	ft_putendl("");ft_putnbr(env->inventory.nb_mendiane);
	ft_putendl("");ft_putnbr(env->inventory.nb_phiras);
	ft_putendl("");ft_putnbr(env->inventory.nb_thystame);
	ft_putendl("");
}