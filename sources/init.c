/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:56:53 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/10/21 15:56:53 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	ft_init(t_env *env, char *args[])
{
	env->amount_philos = ft_atoi(args[0]);
	env->philos = malloc(sizeof(t_philo) * 2);
	env->philos[0].index = 1;
	env->philos[1].index = 2;
}