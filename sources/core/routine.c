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
	pthread_mutex_lock(&philo->e->mutex_print);
	printf("%ld %d is sleeping\n", ft_get_philo_time(philo->e->s_time), philo->index);
	pthread_mutex_unlock(&philo->e->mutex_print);
	ft_usleep(philo->e->t_sleep);
}

static void	ft_put_forks(t_philo *p)
{
	pthread_mutex_lock(&p->e->mutex_fork[p->r_index]);
	p->e->forks[p->r_index] = 0;
	pthread_mutex_unlock(&p->e->mutex_fork[p->r_index]);
	pthread_mutex_lock(&p->e->mutex_fork[p->l_index]);
	p->e->forks[p->l_index] = 0;
	pthread_mutex_unlock(&p->e->mutex_fork[p->l_index]);
}

static int	ft_someone_is_dead(t_philo *p, int flag)
{
	pthread_mutex_lock(&p->e->mutex_died);
	if (flag == 1)
		p->e->one_philo_died = 1;
	if (p->e->one_philo_died == 1)
	{
		pthread_mutex_unlock(&p->e->mutex_died);
		return (1);
	}
	pthread_mutex_unlock(&p->e->mutex_died);
	return (0);
}

static void	ft_check_died_table(t_philo *p)
{
	long int	c_time;

	pthread_mutex_lock(&p->e->mutex_stop);
	c_time = ft_get_current_time();
	if (p->last_meal == 0)
	{
		if (!ft_someone_is_dead(p, 0) && (c_time - p->e->s_time) >= p->e->t_die)
		{
			pthread_mutex_unlock(&p->e->mutex_stop);
			printf("%ld %d is dead\n", ft_get_philo_time(p->e->s_time), p->index);
			ft_someone_is_dead(p, 1);
		}
		pthread_mutex_unlock(&p->e->mutex_stop);
	}
	else
	{
		if (!ft_someone_is_dead(p, 0) && (c_time - p->last_meal) >= p->e->t_die)
		{
			pthread_mutex_unlock(&p->e->mutex_stop);
			printf("%ld %d is dead\n", ft_get_philo_time(p->e->s_time), p->index);
			ft_someone_is_dead(p, 1);
		}
		pthread_mutex_unlock(&p->e->mutex_stop);
	}
}

static int	ft_think_philo(t_philo *philo)
{
	// ft_usleep(philo->t_sleep / 2);
	pthread_mutex_lock(&philo->e->mutex_print);
	printf("%ld %d is thinking\n", ft_get_philo_time(philo->e->s_time), philo->index);
	pthread_mutex_unlock(&philo->e->mutex_print);
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
	philo->last_meal = ft_get_current_time();
	pthread_mutex_lock(&philo->e->mutex_print);
	printf("%ld %d is eating\n", ft_get_philo_time(philo->e->s_time), philo->index);
	pthread_mutex_unlock(&philo->e->mutex_print);
	ft_put_forks(philo);
	ft_usleep(philo->e->t_eat);
	return (0);
}

static int	ft_take_rigth_fork(t_philo *philo)
{
	if (philo->e->forks[philo->r_index] == 0)
	{
		philo->e->forks[philo->r_index] = 1;
		pthread_mutex_lock(&philo->e->mutex_print);
		printf("%ld %d has taken a fork\n", ft_get_philo_time(philo->e->s_time), philo->index);
		pthread_mutex_unlock(&philo->e->mutex_print);
		return (0);
	}
	return (1);
}

static int	ft_take_left_fork(t_philo *philo)
{
	// if (ft_check_died_table(philo))
	// 	return (2);
	if (philo->e->forks[philo->l_index] == 0)
	{
		philo->e->forks[philo->l_index] = 1;
		pthread_mutex_lock(&philo->e->mutex_print);
		printf("%ld %d has taken a fork\n", ft_get_philo_time(philo->e->s_time), philo->index);
		pthread_mutex_unlock(&philo->e->mutex_print);
		return (0);
	}
	return (1);
}

// static int	ft_eat_routine_odd(t_philo *philo)
// {
// 	int	has_taken_fork_r;
// 	int	has_taken_fork_l;

// 	has_taken_fork_r = -1;
// 	has_taken_fork_l = -1;
// 	ft_check_died_table(philo);
// 	if (ft_check_died_table(philo))
// 			return (2);
	
// 	has_taken_fork_r = ft_take_rigth_fork(philo);
// 	if (has_taken_fork_r == 2)
// 		return (2);
// 	else if (has_taken_fork_r == 1)
// 		return (0);
// 	while (1)
// 	{
// 		ft_check_died_table(philo);
// 		if (ft_check_died_table(philo))
// 			return (2);
// 		has_taken_fork_l = ft_take_left_fork(philo);
// 		if (has_taken_fork_l == 2)
// 			return (2);
// 		else if (has_taken_fork_l == 0)
// 			break ;
// 	}
// 	ft_check_died_table(philo);
// 	if (ft_check_died_table(philo))
// 		return (2);
// 	if (ft_get_meal(philo))
// 		return (2);
// 	ft_sleep_philo(philo);
// 	return (0);
// }

// static int	ft_eat_routine_even(t_philo *philo)
// {
// 	int	has_taken_fork_r;
// 	int	has_taken_fork_l;

// 	has_taken_fork_r = -1;
// 	has_taken_fork_l = -1;
// 	ft_check_died_table(philo);
// 	if (ft_check_died_table(philo))
// 			return (2);
// 	has_taken_fork_l = ft_take_left_fork(philo);
// 	if (has_taken_fork_l == 2)
// 		return (2);
// 	else if (has_taken_fork_l == 1)
// 		return (0);
// 	while (1)
// 	{
// 		ft_check_died_table(philo);
// 		if (ft_check_died_table(philo))
// 			return (2);
// 		// pthread_mutex_lock(&philo->mutex_actions);
// 		has_taken_fork_r = ft_take_rigth_fork(philo);
// 		// pthread_mutex_unlock(&philo->mutex_actions);
// 		if (has_taken_fork_r == 2)
// 			return (2);
// 		else if (has_taken_fork_r == 1)
// 		{
// 			// pthread_mutex_lock(&philo->mutex_actions);
// 			philo->e->forks[philo->forks_idx.l] = 0;
// 			// pthread_mutex_unlock(&philo->mutex_actions);
// 			return (0);
// 		}
// 		else if (has_taken_fork_r == 0)
// 			break ;
// 	}
// 	ft_check_died_table(philo);
// 	if (ft_check_died_table(philo))
// 		return (2);
// 	if (ft_get_meal(philo))
// 		return (2);
// 	ft_sleep_philo(philo);
// 	return (0);
// }

static int	ft_get_forks(t_philo *p)
{
	int	has_first_fork;
	int	has_second_fork;

	// if (ft_check_died_table(p))
	// 	return (2);
	pthread_mutex_lock(&p->e->mutex_fork[p->r_index]);
	has_first_fork = ft_take_rigth_fork(p);
	pthread_mutex_unlock(&p->e->mutex_fork[p->r_index]);
	pthread_mutex_lock(&p->e->mutex_fork[p->l_index]);
	has_second_fork = ft_take_left_fork(p);
	pthread_mutex_unlock(&p->e->mutex_fork[p->l_index]);
	return (has_first_fork + has_second_fork);
}

static int	ft_eat(t_philo *p)
{
	int	ready_to_eat;

	while (1)
	{
		ready_to_eat = ft_get_forks(p);
		// if (ft_check_died_table(p))
		// 	return (2);
		if (ready_to_eat == 0)
			break ;
		else if (ready_to_eat == 2)
			return (2);
	}
	ft_get_meal(p);
	ft_sleep_philo(p);
	return (0);
}

void	*ft_philo_routine(t_philo *philo)
{
	if (philo->index % 2 == 0)
		ft_usleep(10);
	while (!ft_someone_is_dead(philo, 0))
	{
		ft_check_died_table(philo);
		if (ft_eat(philo))
			break ;
		ft_think_philo(philo);
	}
	return ((void*)0);
}
