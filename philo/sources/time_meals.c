/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_meals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:57:30 by dnieto-c          #+#    #+#             */
/*   Updated: 2023/02/10 13:34:09 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	ft_get_current_time(void)
{
	t_timer	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

long int	ft_get_philo_time(long int start)
{
	long int	philo_time;

	philo_time = ft_get_current_time() - start;
	return (philo_time);
}

void	ft_usleep(t_philo *p, int milliseconds)
{
	long int	time_diff;

	time_diff = ft_get_current_time() + milliseconds;
	while (ft_get_current_time() < time_diff)
	{
		if (ft_check_death(p))
			break ;
		usleep(1000);
	}
}

int	ft_stay_hungry(t_philo *p)
{
	if (p->times_must_eat == 0)
		return (0);
	else
	{
		if (p->amt_meals == p->times_must_eat)
		{
			pthread_mutex_lock(&p->e->main_mutex);
			p->e->philo_full++;
			if (p->e->philo_full == p->amount_philos)
			{
				if (!p->e->one_philo_died)
				{
					p->e->one_philo_died = 1;
					printf("All philos have eat\n");
				}
				pthread_mutex_unlock(&p->e->main_mutex);
				return (1);
			}
			pthread_mutex_unlock(&p->e->main_mutex);
			return (0);
		}
	}
	return (0);
}
