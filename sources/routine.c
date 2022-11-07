/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:28:10 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/10/29 16:28:10 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_philo_routine(t_env *env)
{
    timer time_start_routine;

    gettimeofday(&time_start_routine, NULL);
    printf("seconds : %ld\nmicro seconds : %ld\n",
    time_start_routine.tv_sec, time_start_routine.tv_usec);
	printf("Amount of philos : %d\n", env->amount_philos);
	printf("Time to die : %d\n", env->time_to_die);
	printf("Time to eat : %d\n", env->time_to_eat);
	printf("Time to sleep : %d\n", env->time_to_sleep);
	printf("Time must eat : %d\n", env->times_must_eat);
    printf("Hello from the thread\n");
	return ((void*)0);
}