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

#include "../includes/philo.h"

void	ft_get_time(void)
{
	timer	time_start_routine;
	suseconds_t	t;

    gettimeofday(&time_start_routine, NULL);
	t = time_start_routine.tv_usec;
	printf("Only seconds :%ld\n", t);
	printf("Only seconds :%ld\n", t / 1000);
}