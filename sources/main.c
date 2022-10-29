/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 09:29:14 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/10/21 09:29:14 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int meals;
pthread_mutex_t mutex;

void	*ft_philo_routine()
{
	for (int i = 0; i < 1000000; i++){
		pthread_mutex_lock(&mutex);
		meals++;
		pthread_mutex_unlock(&mutex);
	}
	return ((void *)0);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	
	(void)argc;
	ft_init(&env, argv);
	pthread_t th[4];
	meals = 0;
	pthread_mutex_init(&mutex, NULL);
	for(int i = 0; i < 4; i++)
	{
		if (pthread_create(th + i, NULL, &ft_philo_routine, NULL))
		return (1);
		printf("Thread number %d starts\n", i);
	}
	for(int i = 0; i < 4; i++)
	{
		if(pthread_join(th[i], NULL))
			return (1);
		printf("Thread number %d finish\n", i);
	}
	printf("Meals : %d\n", meals);
	pthread_mutex_destroy(&mutex);
	return (0);
}
