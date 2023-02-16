/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:06:50 by dnieto-c          #+#    #+#             */
/*   Updated: 2023/02/10 15:06:50 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_someone_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->e->main_mutex);
	philo->e->one_philo_died = 1;
	pthread_mutex_unlock(&philo->e->main_mutex);
}

int	ft_check_death(t_philo *p)
{
	long int	c_time;

	pthread_mutex_lock(&p->e->main_mutex);
	if (p->e->one_philo_died)
	{
		pthread_mutex_unlock(&p->e->main_mutex);
		return (1);
	}
	c_time = ft_get_current_time() - p->last_meal;
	if (c_time >= p->t_die)
	{
		p->e->one_philo_died = 1;
		printf("%ld %d died\n", ft_get_philo_time(p->e->s_time), p->index);
		pthread_mutex_unlock(&p->e->main_mutex);
		return (1);
	}
	pthread_mutex_unlock(&p->e->main_mutex);
	return (0);
}

void	ft_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->e->main_mutex);
	if (philo->e->one_philo_died)
	{
		pthread_mutex_unlock(&philo->e->main_mutex);
		return ;
	}
	printf("%ld %d", ft_get_philo_time(philo->e->s_time), philo->index);
	printf("%s\n", msg);
	pthread_mutex_unlock(&philo->e->main_mutex);
}

int	ft_error_malloc_failed(void)
{
	printf("Malloc failed.\n");
	return (1);
}

int	ft_join_threads_error(void)
{
	printf("Error joining the threads.\n");
	return (1);
}
