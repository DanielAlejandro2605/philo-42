/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:21:50 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/11/15 10:21:50 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

int	ft_init(t_env *env, char *args[])
{
	env->amount_philos = ft_atoi(args[0]);
	env->time_to_die = ft_atoi(args[1]);
	env->time_to_eat = ft_atoi(args[2]);
	env->time_to_sleep = ft_atoi(args[3]);
	if (args[4])
		env->times_must_eat = ft_atoi(args[4]);
	else
		env->times_must_eat = 0;
	return (0);
}

