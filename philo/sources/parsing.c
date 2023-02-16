/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:21:50 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/11/15 10:21:50 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_check_numeric_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_check_args(int argc, char *args[])
{
	long int	check;
	int			i;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid use of the program.\n");
		return (1);
	}
	i = 0;
	while (i < (argc - 1))
	{
		if (ft_check_numeric_args(args[i]))
		{
			printf("Invalid use of the program.\n");
			return (1);
		}
		check = ft_atoi_overflow(args[i]);
		if (check > INT_MAX || check <= 0)
		{
			printf("Invalid use of the program.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static pthread_mutex_t	*ft_init_mutex(int amt_philos)
{
	pthread_mutex_t	*mutex_fork;
	int				i;

	mutex_fork = ft_calloc(sizeof(pthread_mutex_t), amt_philos + 1);
	if (!mutex_fork)
	{
		printf("Malloc failed.\n");
		return (NULL);
	}
	i = 0;
	while (i < amt_philos)
	{
		pthread_mutex_init(&mutex_fork[i], NULL);
		i++;
	}
	return (mutex_fork);
}

static int	*ft_get_forks(int amt_philos)
{
	int		*forks;

	forks = ft_calloc(sizeof(int), amt_philos);
	if (!forks)
	{
		printf("Malloc failed.\n");
		return (NULL);
	}
	return (forks);
}

int	ft_init(t_env *env, int argc, char *args[])
{
	if (ft_check_args(argc, args))
		return (1);
	memset((void *)env, 0, sizeof(t_env));
	env->amount_philos = (int)ft_atoi_overflow(args[0]);
	env->t_die = (int)ft_atoi_overflow(args[1]);
	env->t_eat = (int)ft_atoi_overflow(args[2]);
	env->t_sleep = (int)ft_atoi_overflow(args[3]);
	if (args[4])
		env->times_must_eat = (int)ft_atoi_overflow(args[4]);
	else
		env->times_must_eat = 0;
	env->one_philo_died = 0;
	env->forks = ft_get_forks(env->amount_philos);
	if (!env->forks)
		return (ft_error_malloc_failed());
	env->mutex = ft_init_mutex(env->amount_philos);
	if (!env->mutex)
	{
		free (env->forks);
		return (ft_error_malloc_failed());
	}
	return (0);
}
