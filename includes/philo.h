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

typedef	struct fork
{
	pthread_mutex_t mutex;
	int				index;
	int				forks;
}					t_fork;

typedef union
{
    t_philo philo;
	t_fork	forks;
}	t_item;


typedef struct	list
{
	void			*item;
	struct list		*prev;
	struct list		*next;
}					t_list;

typedef struct timeval timer;

typedef struct environment
{
	int				amount_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	t_list			*guest_philos;
}			t_env;


/*Initialize environnement*/
int		ft_init(t_env *env, char *args[]);
t_list	*ft_set_dinner_table(int amt_philos);
void	ft_init_philo(t_list **begin_lst, int flag_item);
void	ft_push(t_list **begin_lst, void *data, size_t data_size);
/*Routine of each philo*/
void	*ft_philo_routine();
/*Time*/
void	ft_get_time(void);
/*Free memory*/
void    ft_free(t_env *env);
/*Error message for bad use of the program*/
void	ft_error_args(void);
/*Error message when fail to create the threads*/
void    ft_create_threads_error(void);
#endif