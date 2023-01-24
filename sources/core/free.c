/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:54:12 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/11/07 11:54:12 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_free(t_env *env, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < env->amount_philos)
	{
		free (philos[i]);
		i++;
	}
	free (philos);
	free (env->forks);
}