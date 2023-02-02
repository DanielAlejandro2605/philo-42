/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:56:53 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/10/21 15:56:53 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/philo.h"

t_philo**	ft_init_philos(t_env *env)
{
	t_philo **philos;
	int		i;

	philos = ft_calloc(env->amount_philos + 1, sizeof(t_philo *));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < env->amount_philos)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		// Proteger
		pthread_mutex_init(&philos[i]->mutex_died, NULL);
		philos[i]->index = i + 1;
		philos[i]->t_die = env->t_die;
		philos[i]->t_eat = env->t_eat;
		philos[i]->t_sleep = env->t_sleep;
		philos[i]->times_must_eat = env->times_must_eat;
		philos[i]->r_index = i;
		philos[i]->l_index = (i + 1) % env->amount_philos;
		philos[i]->e = env;
		i++;
	}
	philos[i] = NULL;
	return (philos);
}
