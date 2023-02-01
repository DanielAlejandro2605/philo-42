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

#include "../../includes/philo.h"

static int	ft_dinner(t_env *env, t_philo **philos)
{
	int	i;

	i = 0;
	env->s_time = ft_get_current_time();
	pthread_mutex_init(&env->mutex_print, NULL);
	pthread_mutex_init(&env->mutex_died, NULL);
	while (i < env->amount_philos)
	{
		if (pthread_create(&philos[i]->id, NULL, &ft_philo_routine, philos[i]))
			return (ft_create_threads_error());
		i++;
	}
	i = 0;
	while (i < env->amount_philos)
	{
		if (pthread_join(philos[i]->id, NULL))
			return (ft_join_threads_error());
		i++;
	}
	pthread_mutex_destroy(&env->mutex_print);
	pthread_mutex_destroy(&env->mutex_died);
	return (0);
}

static void	ft_print_forks_by_philo(int	amt_philos, t_philo	**philos)
{
	int	i;

	i = 0;
	while (i < amt_philos)
	{
		printf("idx :%d | left %d | rigth %d\n", philos[i]->index, philos[i]->rigth_index,  philos[i]->left_index);
		i++;
	}
}

// static void	ft_init_or_destroy_philo_mutex(t_philo **philos, int amt_philos, int f)
// {
// 	int	i;

// 	i = 0;
// 	if (f == 1)
// 	{
// 		while (i < amt_philos)
// 		{
// 			pthread_mutex_init(&philos[i]->mutex_rigth, NULL);
// 			pthread_mutex_init(&philos[i]->mutex_left, NULL);
// 			pthread_mutex_init(&philos[i]->mutex_died, NULL);
// 			i++;
// 		}
// 	}
// 	else if (f == 2)
// 	{
// 		while (i < amt_philos)
// 		{
// 			pthread_mutex_destroy(&philos[i]->mutex_rigth);
// 			pthread_mutex_destroy(&philos[i]->mutex_left);
// 			pthread_mutex_destroy(&philos[i]->mutex_died);
// 			i++;
// 		}
// 	}
// }

int	main(int argc, char *argv[])
{
	t_env	env;
	t_philo	**philos;

	if(ft_init(&env, argc, argv + 1))
		return (1);
	philos = ft_init_philos(&env);
	if (!philos)
		return (2);
	// if (ft_dinner(&env, philos))
	// 	ft_free(&env, philos);
	// ft_init_or_destroy_philo_mutex(philos, env.amount_philos, 2);
	// ft_free(&env, philos);
}
