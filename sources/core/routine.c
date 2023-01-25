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

#include "../../includes/philo.h"

static void	ft_think_philo(t_philo *philo)
{
	ft_usleep(2);
	pthread_mutex_lock(&philo->ptr_env->mutex_print);
	printf("%ld %d is thinking\n", ft_get_philo_time(philo->ptr_env->start_time_routine), philo->index);
	pthread_mutex_unlock(&philo->ptr_env->mutex_print);
}

static void	ft_sleep_philo(t_philo *philo)
{
	ft_usleep(philo->ptr_env->time_to_sleep);
	pthread_mutex_lock(&philo->ptr_env->mutex_print);
	printf("%ld %d is sleeping\n", ft_get_philo_time(philo->ptr_env->start_time_routine), philo->index);
	pthread_mutex_unlock(&philo->ptr_env->mutex_print);
}

static void	ft_eat_philo(t_philo *philo)
{
	if (philo->ptr_env->forks[philo->forks_idx.l] == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->ptr_env->forks[philo->forks_idx.l] = 1;
		pthread_mutex_lock(&philo->ptr_env->mutex_print);
		printf("%ld %d has taken a fork\n", ft_get_philo_time(philo->ptr_env->start_time_routine), philo->index);
		pthread_mutex_unlock(&philo->ptr_env->mutex_print);
		if (philo->ptr_env->forks[philo->forks_idx.r] == 0)
		{
			printf("%ld %d has taken a fork\n", ft_get_philo_time(philo->ptr_env->start_time_routine), philo->index);
			philo->ptr_env->forks[philo->forks_idx.r] = 1;
			pthread_mutex_lock(&philo->ptr_env->mutex_print);
			printf("%ld %d  is eating\n", ft_get_philo_time(philo->ptr_env->start_time_routine), philo->index);
			pthread_mutex_unlock(&philo->ptr_env->mutex_print);
			ft_usleep(philo->ptr_env->time_to_eat);
			philo->ptr_env->forks[philo->forks_idx.l] = 0;
			philo->ptr_env->forks[philo->forks_idx.r] = 0;
			pthread_mutex_unlock(&philo->mutex);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->ptr_env->mutex_print);
		printf("Hay algo ocupado? %d\n", philo->index);
		pthread_mutex_unlock(&philo->ptr_env->mutex_print);
	}
}

void	*ft_philo_routine(t_philo *philo)
{
	pthread_mutex_init(&philo->mutex, NULL);
	while (1)
	{
		if (philo->index % 2 == 0 && philo->index % 3 == 0)
			ft_usleep(1);
		if (philo->index % 2 == 0)
		{
			ft_sleep_philo(philo);
			ft_eat_philo(philo);
			ft_think_philo(philo);
		}
		else
		{
			ft_eat_philo(philo);
			ft_think_philo(philo);
			ft_sleep_philo(philo);
		}

	}
	pthread_mutex_destroy(&philo->mutex);
	return ((void*)0);
}
