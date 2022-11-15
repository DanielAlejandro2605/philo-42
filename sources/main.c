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

static void	ft_dinner(t_env *env)
{
	t_list		*philos;
	t_list		*aux_philos;
	t_philo		*philo_aux;
	int			*forks;
	int			i;

	philos = ft_set_dinner_table(env, &forks);
	if (!philos || !forks)
		printf("Error\n");
	aux_philos = philos;
	i = 0;
	while (i < env->amount_philos)
	{
		philo_aux = (t_philo *)philos->item;
		philo_aux->forks = forks;
		if (pthread_create(&philo_aux->id, NULL, &ft_philo_routine, philo_aux) != 0)
			printf("Error to create the thread\n");
		philos = philos->next;
		i++;
	}
	philos = aux_philos;
	i = 0;
	while (i < env->amount_philos)
	{
		philo_aux = (t_philo *)philos->item;
		if(pthread_join(philo_aux->id, NULL) != 0)
			printf("Error to join the thread\n");
		philos = philos->next;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_env	env;
	
	if (argc < 5 || argc > 6)
		ft_error_args();
	if(ft_init(&env, argv + 1))
		ft_create_threads_error();
	ft_dinner(&env);
	// ft_free(&env);
}
