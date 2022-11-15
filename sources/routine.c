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

// static t_forks ft_get_index_forks(int philo_index, int amt_philos)
// {
// 	t_forks	forks;

// 	if (philo_index == 0)
// 	{
// 		forks.left_fork = 0;
// 		forks.rigth_fork = amt_philos - 1;
// 	}
// 	else
// 	{
// 		forks.left_fork = philo_index;
// 		forks.rigth_fork = philo_index - 1;
// 	}
// 	return forks;
// }

void	*ft_philo_routine(t_philo *philo)
{
	// int	i;
	// t_forks	forks_to_used;

	// (void)forks_to_used;
	// printf("%d\n", env->amount_philos);
	// // pthread_mutex_t mutex;
	// // usleep(10000);
	// // pthread_mutex_init(&mutex, NULL);
	// // pthread_mutex_lock(&mutex);
	if(philo->index % 2 == 0)
	{
		usleep(philo->time_to_sleep);
		philo->forks[0] = 100;
		printf("I am philo %d and I use the fork %d\n", philo->index, philo->forks[0]);
		return ((void*)0);
	}	
	philo->forks[0] = 100;
	printf("I am philo %d and I use the fork %d\n", philo->index, philo->forks[0]);
	philo->forks[0] = 1;
	// i = 0;
	// while (i < 2)
	// {
	// 	printf("I am the fork %d\n", philo->forks[i]);
	// 	i++;
	// }	
	// pthread_mutex_unlock(&mutex);
	// pthread_mutex_destroy(&mutex);
	// ft_get_time();
	// pthread_mutex_lock(&env->mutex);
	// printf("Philo %d\n", env->philo_id);
	// printf("Rigth %d - Left %d\n", env->forks[env->philo_forks->rigth_fork], env->forks[env->philo_forks->left_fork]);	//printf("IN THREAD : Fork rigth %d, Fork left : %d\n", env->philo_forks->rigth_fork, env->philo_forks->left_fork);
	// pthread_mutex_unlock(&env->mutex);
	// printf("Amount of philos : %d\n", env->amount_philos);
	// printf("Time to die : %d\n", env->time_to_die);
	// printf("Time to eat : %d\n", env->time_to_eat);
	// printf("Time to sleep : %d\n", env->time_to_sleep);
	// printf("Time must eat : %d\n", env->times_must_eat);
    // printf("Hello from the thread\n");
	return ((void*)0);
}