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
	ft_usleep(1);
	pthread_mutex_lock(&philo->e->mutex_print);
	printf("%ld %d is thinking\n", ft_get_philo_time(philo->e->s_time), philo->index);
	pthread_mutex_unlock(&philo->e->mutex_print);
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->e->forks[philo->forks_idx.l] = 1;
		pthread_mutex_unlock(&philo->mutex);
	}
}

static void	ft_sleep_philo(t_philo *philo)
{
	ft_usleep(philo->e->t_sleep);
	pthread_mutex_lock(&philo->e->mutex_print);
	printf("%ld %d is sleeping\n", ft_get_philo_time(philo->e->s_time), philo->index);
	pthread_mutex_unlock(&philo->e->mutex_print);
}

static void	ft_eat_philo(t_philo *philo)
{
	if (philo->e->forks[philo->forks_idx.l] == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->e->forks[philo->forks_idx.l] = 1;
		pthread_mutex_lock(&philo->e->mutex_print);
		printf("%ld %d has taken a fork\n", ft_get_philo_time(philo->e->s_time), philo->index);
		pthread_mutex_unlock(&philo->e->mutex_print);
		if (philo->e->forks[philo->forks_idx.r] == 0)
		{
			printf("%ld %d has taken a fork\n", ft_get_philo_time(philo->e->s_time), philo->index);
			philo->e->forks[philo->forks_idx.r] = 1;
			pthread_mutex_lock(&philo->e->mutex_print);
			printf("%ld %d  is eating\n", ft_get_philo_time(philo->e->s_time), philo->index);
			pthread_mutex_unlock(&philo->e->mutex_print);
			ft_usleep(philo->e->t_eat);
			philo->e->forks[philo->forks_idx.l] = 0;
			philo->e->forks[philo->forks_idx.r] = 0;
			pthread_mutex_unlock(&philo->mutex);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->e->mutex_print);
		printf("Hay algo ocupado? %d\n", philo->index);
		pthread_mutex_unlock(&philo->e->mutex_print);
	}
}

// static int	ft_philo_even(t_philo *philo)
// {
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->mutex);
// 		if (philo->e->forks[philo->forks_idx.r] == 0)
// 		{
// 			philo->e->forks[philo->forks_idx.r] = 1;
// 			if (philo->e->forks[philo->forks_idx.l] == -1)
// 			{
// 				printf("SI\n");
// 				sleep(1);
// 				exit (1);
// 			}
// 			if (philo->e->forks[philo->forks_idx.l] == 0)
// 			{
// 				philo->e->forks[philo->forks_idx.l] = 1;
// 				ft_usleep(philo->e->t_eat);
// 				pthread_mutex_lock(&philo->e->mutex_print);
// 				printf("%ld %d is eating\n", ft_get_philo_time(philo->e->s_time), philo->index);
// 				pthread_mutex_unlock(&philo->e->mutex_print);
// 				philo->e->forks[philo->forks_idx.r] = 0;
// 				philo->e->forks[philo->forks_idx.l] = 0;
// 				pthread_mutex_unlock(&philo->mutex);
// 				ft_sleep_philo(philo);
// 			}
// 			else
// 			{
// 				philo->e->forks[philo->forks_idx.r] = 0;
// 				pthread_mutex_unlock(&philo->mutex);
// 			}
// 		}
// 		else
// 			pthread_mutex_unlock(&philo->mutex);
// 		// Thinking
// 		ft_usleep(1);
// 		pthread_mutex_lock(&philo->e->mutex_print);
// 		printf("%ld %d is thinking\n", ft_get_philo_time(philo->e->s_time), philo->index);
// 		pthread_mutex_unlock(&philo->e->mutex_print);
// 	}
// }

static int	ft_put_forks(t_philo *p)
{
	p->e->forks[p->forks_idx.r] = 0;
	p->e->forks[p->forks_idx.l] = 0;
}

static int	ft_check_died_time(t_philo *p)
{
	if (p->last_meal == 0)
	{
		if ((ft_get_current_time() - p->e->s_time) >= p->e->t_die)
		{
			pthread_mutex_lock(&p->e->mutex_print);
			printf("%ld %d is died\n", ft_get_philo_time(p->e->s_time), p->index);
			pthread_mutex_unlock(&p->e->mutex_print);
			return (1);
		}
	}
	else
	{
		if ((ft_get_current_time() - p->last_meal) >= p->e->t_die)
		{
			pthread_mutex_lock(&p->e->mutex_print);
			printf("%ld %d is died\n", ft_get_philo_time(p->e->s_time), p->index);
			pthread_mutex_unlock(&p->e->mutex_print);
			return (1);
		}
	}
	return (0);
}

static int	ft_take_rigth_fork(t_philo *philo)
{
	if (philo->e->forks[philo->forks_idx.r] == 0)
	{
		philo->e->forks[philo->forks_idx.r] = 1;
		pthread_mutex_lock(&philo->e->mutex_print);
		printf("%ld %d has taken a fork\n", ft_get_philo_time(philo->e->s_time), philo->index);
		pthread_mutex_unlock(&philo->e->mutex_print);
		return (1);
	}
	return (0);
}

static int	ft_take_left_fork(t_philo *philo)
{
	if (philo->e->forks[philo->forks_idx.l] == 0)
	{
		philo->e->forks[philo->forks_idx.l] = 1;
		pthread_mutex_lock(&philo->e->mutex_print);
		printf("%ld %d has taken a fork\n", ft_get_philo_time(philo->e->s_time), philo->index);
		pthread_mutex_unlock(&philo->e->mutex_print);
		return (1);
	}
	return (0);
}

static int	ft_philo_odd(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (ft_take_rigth_fork(philo))
		{
			if (ft_take_left_fork(philo))
			{
				philo->last_meal = ft_get_current_time();
				ft_usleep(philo->e->t_eat);
				pthread_mutex_lock(&philo->e->mutex_print);
				printf("%ld %d is eating\n", ft_get_philo_time(philo->e->s_time), philo->index);
				pthread_mutex_unlock(&philo->e->mutex_print);
				ft_put_forks(philo);
			}
			else
			{
				if (ft_check_died_time(philo))
				{
					pthread_mutex_unlock(&philo->mutex);
					return (1);
				}
			}
		}
		else
		{
			if (ft_check_died_time(philo))
			{
				pthread_mutex_unlock(&philo->mutex);
				return (1);
			}
		}
		pthread_mutex_unlock(&philo->mutex);
		// pthread_mutex_lock(&philo->mutex);
		// if (philo->e->forks[philo->forks_idx.l] == 0)
		// {

		// 	// if (philo->e->forks[philo->forks_idx.r] == 0)
		// 	// {
		// 	// 	philo->e->forks[philo->forks_idx.l] = 1;
		// 	// 	philo->e->forks[philo->forks_idx.r] = 1;
		// 	// 	pthread_mutex_lock(&philo->e->mutex_print);
		// 	// 	printf("%ld %d is eating\n", ft_get_philo_time(philo->e->s_time), philo->index);
		// 	// 	pthread_mutex_unlock(&philo->e->mutex_print);
		// 	// 	ft_usleep(philo->e->t_eat);
		// 	// 	philo->e->forks[philo->forks_idx.l] = 0;
		// 	// 	philo->e->forks[philo->forks_idx.r] = 0;
		// 	// 	pthread_mutex_unlock(&philo->mutex);
		// 	// 	ft_sleep_philo(philo);
		// 	// }
		// 	// else
		// 	// {
		// 	// 	philo->e->forks[philo->forks_idx.l] = 0;
		// 	// 	pthread_mutex_unlock(&philo->mutex);
		// 	// }
		// }
		// else
		// 	pthread_mutex_unlock(&philo->mutex);
		// // Thinking
		// ft_usleep(1);
		// pthread_mutex_lock(&philo->e->mutex_print);
		// printf("%ld %d is thinking\n", ft_get_philo_time(philo->e->s_time), philo->index);
		// pthread_mutex_unlock(&philo->e->mutex_print);
		// if (ft_check_died_time(philo))
		// {
		// 	pthread_mutex_lock(&philo->mutex);
		// 	philo->e->one_philo_died = 1;
		// 	pthread_mutex_unlock(&philo->mutex);
		// }
	}
}

void	*ft_philo_routine(t_philo *philo)
{
	pthread_mutex_init(&philo->mutex, NULL);
	while (1)
	{
		if (ft_philo_odd(philo))
			break ;
		// if (philo->index % 2 == 0)
		// {
		// 	ft_philo_even(philo);
		// }
		// else
		// {
		// }
	}
	pthread_mutex_destroy(&philo->mutex);
	return ((void*)0);
}
