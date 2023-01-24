/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:10:12 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/11/07 17:10:12 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

long int	ft_get_current_time(void)
{
	timer	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
}

long int	ft_get_philo_time(long int start)
{
	long int	philo_time;

	printf("start %ld\n", start);
	philo_time = ft_get_current_time() - start;
	printf("philo time %ld\n", philo_time);
	return (philo_time);
}
