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
	env->start_time_routine = ft_get_current_time();
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
	return (0);
}

// static void	ft_dinner(t_env *env)
// {
// 	t_list		*philos;
// 	t_list		*aux_philos;
// 	t_philo		*philo_aux;
// 	int			*forks;
// 	int			i;

// 	philos = ft_set_dinner_table(env, &forks);
// 	if (!philos || !forks)
// 		printf("Error\n");
// 	aux_philos = philos;
// 	i = 0;
// 	while (i < env->amount_philos)
// 	{
// 		philo_aux = (t_philo *)philos->item;
// 		philo_aux->forks = forks;
// 		if (pthread_create(&philo_aux->id, NULL, &ft_philo_routine, philo_aux) != 0)
// 			printf("Error to create the thread\n");
// 		philos = philos->next;
// 		i++;
// 	}
// 	philos = aux_philos;
// 	i = 0;
// 	while (i < env->amount_philos)
// 	{
// 		philo_aux = (t_philo *)philos->item;
// 		if(pthread_join(philo_aux->id, NULL) != 0)
// 			printf("Error to join the thread\n");
// 		philos = philos->next;
// 		i++;
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
	ft_dinner(&env, philos);
	ft_free(&env, philos);
}
