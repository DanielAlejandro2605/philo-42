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

static int	ft_init_or_destroy_dinner_mutex(t_env *env, int flag)
{
	if (flag == 1)
	{
		if (pthread_mutex_init(&env->mutex_print, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&env->mutex_died, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&env->mutex_stop, NULL) != 0)
			return (1);
	}
	else if (flag == 2)
	{
		if (pthread_mutex_destroy(&env->mutex_print) != 0)
			return (1);
		if (pthread_mutex_destroy(&env->mutex_died) != 0)
			return (1);
		if (pthread_mutex_destroy(&env->mutex_stop) != 0)
			return (1);
	}
	return (0);
}

static int	ft_create_threads(t_env *env, t_philo **philos)
{
	int	i;

	if (ft_init_or_destroy_dinner_mutex(env, 1))
		return (1);
	env->s_time = ft_get_current_time();
	i = -1;
	while (++i < env->amount_philos)
	{
		if (pthread_create(&philos[i]->id, NULL, &ft_philo_routine, philos[i]))
		{
			while (i-- >= 0)
			{
				if (pthread_join(philos[i]->id, NULL))
					return (ft_join_threads_error());
			}
			if (ft_init_or_destroy_dinner_mutex(env, 2))
				return (1);
			return (0);
		}
	}
	return (0);
}

static int	ft_dinner(t_env *env, t_philo **philos)
{
	int	i;

	if (ft_init_or_destroy_dinner_mutex(env, 1))
		return (1);
	if (ft_create_threads(env, philos))
		return (1);
	i = -1;
	while (++i < env->amount_philos)
	{
		if (pthread_join(philos[i]->id, NULL))
			return (ft_join_threads_error());
	}
	if (ft_init_or_destroy_dinner_mutex(env, 2))
				return (1);
	return (0);
}

static void	ft_print_forks_by_philo(int	amt_philos, t_philo	**philos)
{
	int	i;

	i = 0;
	while (i < amt_philos)
	{
		printf("idx :%d | left %d | rigth %d\n", philos[i]->index, philos[i]->r_index,  philos[i]->l_index);
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
	ft_print_forks_by_philo(env.amount_philos, philos);
	if (ft_dinner(&env, philos))
	{
		printf("Error creating the threads or initialize/destroy mutex\n");
		ft_free(&env, philos);
	}
	ft_free(&env, philos);
}
