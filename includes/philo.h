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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long int		start_time_routine;
	int				*forks;
}					t_env;

typedef struct philo
{
	pthread_t		id;
	pthread_mutex_t mutex;
	int				index;
	int				last_meal;
	int				amt_meals;
	t_env			*ptr_env;
}				t_philo;

typedef	struct fork
{
	pthread_mutex_t mutex;
	int				index;
	int				forks;
}					t_fork;

typedef struct	forks
{
	int			rigth_fork;
	int			left_fork;
}				t_forks;

typedef struct	list
{
	void			*item;
	struct list		*prev;
	struct list		*next;
}					t_list;

typedef struct timeval timer;


/*Parsing of arguments and initialization of environnement*/
int			ft_init(t_env *env, int argc, char *args[]);
/*Creation of array of philos*/
t_philo**	ft_init_philos(t_env *env);
/*Create linked list of philos*/
t_list		*ft_set_dinner_table(t_env *env, int **forks);
/*Routine of each philo*/
void		*ft_philo_routine();
/*Time*/
long int	ft_get_current_time(void);
long int	ft_get_philo_time(long int start);
/*Free memory*/
void		ft_free(t_env *env, t_philo **philos);
/*Error message for bad use of the program*/
int			ft_error_args(void);
int			ft_error_malloc_failed(void);
/*Error message when fail to create the threads*/
int			ft_create_threads_error(void);
int			ft_join_threads_error(void);
#endif