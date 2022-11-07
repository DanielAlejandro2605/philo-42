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
 #include <sys/time.h>
# include "./utils.h"

typedef struct philo
{
	pthread_t	id;
	int			index;
}				t_philo;

typedef struct timeval timer;

typedef struct environment
{
	int				amount_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pthread_t		*array_thread_id;
	pthread_mutex_t mutex;
	t_philo			*philos;
}			t_env;


/*Initialize environnement*/
int		ft_init(t_env *env, char *args[]);
/*Routine of each philo*/
void	*ft_philo_routine();
/*Free memory*/
void    ft_free(t_env *env);
/*Error message for bad use of the program*/
void	ft_error_args(void);
/*Error message when fail to create the threads*/
void    ft_create_threads_error(void);
#endif