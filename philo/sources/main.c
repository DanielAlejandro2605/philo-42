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

static void	ft_free(t_env *env, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < env->amount_philos)
	{
		pthread_mutex_destroy(&philos[i]->vitals);
		free (philos[i]);
		i++;
	}
	free (philos);
	free (env->forks);
	free (env->mutex);
	pthread_mutex_destroy(&env->main_mutex);
}

static int	ft_init_philos(t_env *env, t_philo **philos)
{
	int		i;

	i = -1;
	while (++i < env->amount_philos)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (!philos[i])
		{
			free (philos);
			return (1);
		}
		philos[i]->amount_philos = env->amount_philos;
		philos[i]->index = i + 1;
		philos[i]->t_die = env->t_die;
		philos[i]->t_eat = env->t_eat;
		philos[i]->t_sleep = env->t_sleep;
		philos[i]->times_must_eat = env->times_must_eat;
		philos[i]->r_index = i;
		philos[i]->l_index = (i + 1) % env->amount_philos;
		philos[i]->e = env;
	}
	philos[i] = NULL;
	return (0);
}

static int	ft_create_threads(t_env *env, t_philo **philos)
{
	int	i;

	env->s_time = ft_get_current_time();
	i = -1;
	while (++i < env->amount_philos)
	{
		if (pthread_create(&philos[i]->id, NULL, &ft_philo_routine, philos[i]))
		{
			printf("Error creating thread #%d\n", i);
			printf("The simulation will only have %d philos\n", i);
			while (i-- >= 0)
			{
				if (pthread_join(philos[i]->id, NULL))
					return (ft_join_threads_error());
			}
			if (pthread_mutex_destroy(&env->main_mutex) != 0)
				return (1);
			return (0);
		}
	}
	return (0);
}

static int	ft_dinner(t_env *env, t_philo **philos)
{
	int	i;

	if (pthread_mutex_init(&env->main_mutex, NULL) != 0)
		return (1);
	if (ft_create_threads(env, philos))
		return (1);
	i = -1;
	while (++i < env->amount_philos)
	{
		if (pthread_join(philos[i]->id, NULL))
			return (ft_join_threads_error());
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	t_philo	**philos;

	if (ft_init(&env, argc, argv + 1))
		return (1);
	philos = ft_calloc(env.amount_philos + 1, sizeof(t_philo *));
	if (!philos)
	{
		free (env.forks);
		free (env.mutex);
		pthread_mutex_destroy(&env.main_mutex);
		return (1);
	}
	if (ft_init_philos(&env, philos))
	{
		ft_free(&env, philos);
		return (1);
	}
	if (ft_dinner(&env, philos))
		printf("Error creating the threads or initialize/destroy mutex\n");
	ft_free(&env, philos);
	return (0);
}
