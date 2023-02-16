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

static int	ft_put_forks(t_philo *p)
{
	pthread_mutex_lock(&p->e->mutex[p->r_index]);
	p->e->forks[p->r_index] = 0;
	pthread_mutex_unlock(&p->e->mutex[p->r_index]);
	pthread_mutex_lock(&p->e->mutex[p->l_index]);
	p->e->forks[p->l_index] = 0;
	pthread_mutex_unlock(&p->e->mutex[p->l_index]);
	if (ft_stay_hungry(p))
		return (1);
	p->rigth_hand = 0;
	p->left_hand = 0;
	ft_msg(p, " is sleeping");
	ft_usleep(p, p->t_sleep);
	ft_msg(p, " is thinking");
	return (0);
}

static void	ft_get_one_fork(t_philo *p, int fork_side)
{
	int	fork_index;

	if (fork_side == 1)
		fork_index = p->r_index;
	else
		fork_index = p->l_index;
	if (p->e->forks[fork_index] == 0)
	{
		p->e->forks[fork_index] = 1;
		ft_msg(p, " has taken a fork");
		if (fork_side == 1)
			p->rigth_hand = 1;
		else
			p->left_hand = 1;
	}
}

static int	ft_get_forks(t_philo *p)
{
	while ((p->rigth_hand + p->left_hand) != 2)
	{
		pthread_mutex_lock(&p->e->mutex[p->r_index]);
		ft_get_one_fork(p, RIGTH);
		pthread_mutex_unlock(&p->e->mutex[p->r_index]);
		if (ft_check_death(p))
			return (1);
		pthread_mutex_lock(&p->e->mutex[p->l_index]);
		ft_get_one_fork(p, LEFT);
		pthread_mutex_unlock(&p->e->mutex[p->l_index]);
		if (ft_check_death(p))
			return (1);
	}
	return (0);
}

static int	ft_eat(t_philo *philo)
{
	int	status_meal;

	status_meal = 0;
	pthread_mutex_lock(&philo->vitals);
	philo->last_meal = ft_get_current_time();
	pthread_mutex_unlock(&philo->vitals);
	ft_msg(philo, " is eating");
	ft_usleep(philo, philo->e->t_eat);
	philo->amt_meals++;
	if (ft_put_forks(philo))
		status_meal = 1;
	return (status_meal);
}

void	*ft_philo_routine(void *p)
{
	t_philo	*philo;
	int		ready_to_eat;

	philo = (t_philo *)p;
	philo->last_meal = philo->e->s_time;
	if (philo->index % 2 == 0)
		usleep(10000);
	while (1)
	{
		ready_to_eat = ft_get_forks(philo);
		if (ready_to_eat == 0)
		{
			if (ft_check_death(philo))
				break ;
			if (ft_eat(philo))
				break ;
		}
		else
			break ;
	}
	return ((void *)0);
}
