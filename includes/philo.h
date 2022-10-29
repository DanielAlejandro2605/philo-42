/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 09:30:35 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/10/21 09:30:35 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include "./utils.h"

typedef struct philo
{
	pthread_t	id;
	int			index;
}				t_philo;

typedef struct environment
{
	int		amount_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_must_eat;
	t_philo	*philos;
}			t_env;


/*Initialize environnement*/
void	ft_init(t_env *env, char *args[]);
/*Routine of each philo*/
void	*ft_philo_routine();
#endif