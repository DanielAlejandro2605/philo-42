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

static void	ft_sleep_philo(t_philo *philo)
{
	ft_usleep(philo->e->t_sleep);
	pthread_mutex_lock(&philo->e->mutex_print);
	printf("%ld %d is sleeping\n", ft_get_philo_time(philo->e->s_time), philo->index);
	pthread_mutex_unlock(&philo->e->mutex_print);
}

static void	ft_put_forks(t_philo *p)
{
	p->e->forks[p->forks_idx.r] = 0;
	p->e->forks[p->forks_idx.l] = 0;
}

static int	ft_check_died_table(t_philo *p)
{
	pthread_mutex_lock(&p->e->mutex_died);
	if (p->e->one_philo_died == 1)
	{
		pthread_mutex_unlock(&p->e->mutex_died);
		return (1);
	}
	pthread_mutex_unlock(&p->e->mutex_died);
	return (0);
}

static void	ft_check_died_time(t_philo *p)
{
	pthread_mutex_lock(&p->mutex_died);
	if (p->last_meal == 0)
	{
		if ((ft_get_current_time() - p->e->s_time) >= p->e->t_die)
		{
			pthread_mutex_lock(&p->e->mutex_print);
			printf("%ld %d is died\n", ft_get_philo_time(p->e->s_time), p->index);
			pthread_mutex_unlock(&p->e->mutex_print);
			p->e->one_philo_died = 1;
		}
	}
	else
	{
		if ((ft_get_current_time() - p->last_meal) >= p->e->t_die)
		{
			pthread_mutex_lock(&p->e->mutex_print);
			printf("%ld %d is died\n", ft_get_philo_time(p->e->s_time), p->index);
			pthread_mutex_unlock(&p->e->mutex_print);
			p->e->one_philo_died = 1;
		}
	}
	pthread_mutex_unlock(&p->mutex_died);
}

static int	ft_think_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->e->mutex_print);
	printf("%ld %d is thinking\n", ft_get_philo_time(philo->e->s_time), philo->index);
	pthread_mutex_unlock(&philo->e->mutex_print);
	ft_check_died_time(philo);
	return (0);
}

// static int	ft_take_rigth_fork(t_philo *philo)
// {
// 	if (ft_check_died_table(philo))
// 		return (2);
// 	pthread_mutex_lock(&philo->mutex_actions);
// 	if (philo->e->forks[philo->forks_idx.r] == 0)
// 	{
// 		philo->e->forks[philo->forks_idx.r] = 1;
// 		pthread_mutex_lock(&philo->e->mutex_print);
// 		printf("%ld %d has taken a fork rigth\n", ft_get_philo_time(philo->e->s_time), philo->index);
// 		pthread_mutex_unlock(&philo->e->mutex_print);
// 		pthread_mutex_unlock(&philo->mutex_actions);
// 	}
// 	pthread_mutex_unlock(&philo->mutex_actions);
// 	return (0);
// }

// static int	ft_take_left_fork(t_philo *philo)
// {
// 	if (ft_check_died_table(philo))
// 		return (2);
// 	pthread_mutex_lock(&philo->mutex_actions);
// 	if (philo->e->forks[philo->forks_idx.l] == 0)
// 	{
// 		philo->e->forks[philo->forks_idx.l] = 1;
// 		pthread_mutex_lock(&philo->e->mutex_print);
// 		printf("%ld %d has taken a fork left\n", ft_get_philo_time(philo->e->s_time), philo->index);
// 		pthread_mutex_unlock(&philo->e->mutex_print);
// 		pthread_mutex_unlock(&philo->mutex_actions);
// 	}
// 	pthread_mutex_unlock(&philo->mutex_actions);
// 	return (0);
// }

static int	ft_get_meal(t_philo *philo)
{
	if (ft_check_died_table(philo))
		return (2);
	// pthread_mutex_lock(&philo->mutex_actions);
	philo->last_meal = ft_get_current_time();
	pthread_mutex_lock(&philo->e->mutex_print);
	printf("%ld %d is eating\n", ft_get_philo_time(philo->e->s_time), philo->index);
	ft_put_forks(philo);
	pthread_mutex_unlock(&philo->e->mutex_print);
	ft_usleep(philo->e->t_eat);
	// pthread_mutex_unlock(&philo->mutex_actions);
	return (0);
}

static int	ft_take_rigth_fork(t_philo *philo)
{
	if (ft_check_died_table(philo))
		return (2);
	if (philo->e->forks[philo->forks_idx.r] == 0)
	{
		philo->e->forks[philo->forks_idx.r] = 1;
		pthread_mutex_lock(&philo->e->mutex_print);
		printf("%ld %d has taken a fork rigth\n", ft_get_philo_time(philo->e->s_time), philo->index);
		pthread_mutex_unlock(&philo->e->mutex_print);
		return (0);
	}
	return (1);
}

static int	ft_take_left_fork(t_philo *philo)
{
	if (ft_check_died_table(philo))
		return (2);
	if (philo->e->forks[philo->forks_idx.l] == 0)
	{
		philo->e->forks[philo->forks_idx.l] = 1;
		pthread_mutex_lock(&philo->e->mutex_print);
		printf("%ld %d has taken a fork left\n", ft_get_philo_time(philo->e->s_time), philo->index);
		pthread_mutex_unlock(&philo->e->mutex_print);
		return (0);
	}
	return (1);
}

static int	ft_eat_routine_odd(t_philo *philo)
{
	int	has_taken_fork_r;
	int	has_taken_fork_l;

	has_taken_fork_r = -1;
	has_taken_fork_l = -1;
	ft_check_died_time(philo);
	if (ft_check_died_table(philo))
			return (2);
	
	has_taken_fork_r = ft_take_rigth_fork(philo);
	if (has_taken_fork_r == 2)
		return (2);
	else if (has_taken_fork_r == 1)
		return (0);
	while (1)
	{
		ft_check_died_time(philo);
		if (ft_check_died_table(philo))
			return (2);
		has_taken_fork_l = ft_take_left_fork(philo);
		if (has_taken_fork_l == 2)
			return (2);
		else if (has_taken_fork_l == 0)
			break ;
	}
	ft_check_died_time(philo);
	if (ft_check_died_table(philo))
		return (2);
	if (ft_get_meal(philo))
		return (2);
	ft_sleep_philo(philo);
	return (0);
}

static int	ft_eat_routine_even(t_philo *philo)
{
	int	has_taken_fork_r;
	int	has_taken_fork_l;

	has_taken_fork_r = -1;
	has_taken_fork_l = -1;
	ft_check_died_time(philo);
	if (ft_check_died_table(philo))
			return (2);
	has_taken_fork_l = ft_take_left_fork(philo);
	if (has_taken_fork_l == 2)
		return (2);
	else if (has_taken_fork_l == 1)
		return (0);
	while (1)
	{
		ft_check_died_time(philo);
		if (ft_check_died_table(philo))
			return (2);
		// pthread_mutex_lock(&philo->mutex_actions);
		has_taken_fork_r = ft_take_rigth_fork(philo);
		// pthread_mutex_unlock(&philo->mutex_actions);
		if (has_taken_fork_r == 2)
			return (2);
		else if (has_taken_fork_r == 1)
		{
			// pthread_mutex_lock(&philo->mutex_actions);
			philo->e->forks[philo->forks_idx.l] = 0;
			// pthread_mutex_unlock(&philo->mutex_actions);
			return (0);
		}
		else if (has_taken_fork_r == 0)
			break ;
	}
	ft_check_died_time(philo);
	if (ft_check_died_table(philo))
		return (2);
	if (ft_get_meal(philo))
		return (2);
	ft_sleep_philo(philo);
	return (0);
}

static int	ft_get_forks(t_philo *philo)
{
	int	has_first_fork;
	int	has_second_fork;

	ft_check_died_time(philo);
	if (ft_check_died_table(philo))
		return (2);
	pthread_mutex_lock(&philo->mutex_rigth);
	if (ft_take_rigth_fork(philo) == 0)
	{
		pthread_mutex_lock(&philo->mutex_left);
		if (ft_take_left_fork(philo) == 0)
		{
			ft_get_meal(philo);
			pthread_mutex_unlock(&philo->mutex_left);
			pthread_mutex_unlock(&philo->mutex_rigth);
			return (0);
		}
		pthread_mutex_unlock(&philo->mutex_left);
		pthread_mutex_unlock(&philo->mutex_rigth);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex_rigth);
	return (1);
}

static int	ft_eat(t_philo *philo)
{
	int	has_first_fork;
	int	has_second_fork;

	ft_check_died_time(philo);
	if (ft_check_died_table(philo))
		return (2);
	ft_get_forks(philo);
	return (0);
}

void	*ft_philo_routine(t_philo *philo)
{
	pthread_mutex_init(&philo->mutex_rigth, NULL);
	pthread_mutex_init(&philo->mutex_left, NULL);
	pthread_mutex_init(&philo->mutex_died, NULL);
	if (philo->index % 2 == 0)
		ft_usleep(philo->e->t_eat / 2);
	while (1)
	{
		if (ft_eat(philo))
			break ;
		// ft_think_philo(philo);
	}
	pthread_mutex_destroy(&philo->mutex_rigth);
	pthread_mutex_destroy(&philo->mutex_left);
	pthread_mutex_destroy(&philo->mutex_died);
	return ((void*)0);
}
