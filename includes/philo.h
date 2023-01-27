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

# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include "./utils.h"

typedef struct environment
{
	int				amount_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				times_must_eat;
	int				one_philo_died;
	long int		s_time;
	pthread_mutex_t mutex_print;
	int				*forks;
}					t_env;

typedef struct	forks
{
	int			r;
	int			l;
}				t_forks;

typedef struct philo
{
	pthread_t		id;
	pthread_mutex_t mutex;
	int				index;
	int				amt_meals;
	long int		last_meal;
	t_forks			forks_idx;
	t_env			*e;
}					t_philo;

typedef struct timeval timer;

/*Parsing of arguments and initialization of environnement*/
int			ft_init(t_env *env, int argc, char *args[]);
/*Creation of array of philos*/
t_philo**	ft_init_philos(t_env *env);
/*Create linked list of philos*/
// t_list		*ft_set_dinner_table(t_env *env, int **forks);
/*Routine of each philo*/
void		*ft_philo_routine();
/*Time*/
long int	ft_get_current_time(void);
long int	ft_get_philo_time(long int start);
void		ft_usleep(int milliseconds);
/*Free memory*/
void		ft_free(t_env *env, t_philo **philos);
/*Error message for bad use of the program*/
int			ft_error_args(void);
int			ft_error_malloc_failed(void);
/*Error message when fail to create the threads*/
int			ft_create_threads_error(void);
int			ft_join_threads_error(void);
#endif