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

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h> 

# define RIGTH 1
# define LEFT 2
# define INT_MAX 2147483647

typedef struct environment
{
	int				amount_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				times_must_eat;
	int				one_philo_died;
	int				philo_full;
	long int		s_time;
	int				*forks;
	pthread_mutex_t	main_mutex;
	pthread_mutex_t	*mutex;
}					t_env;

typedef struct philo
{
	pthread_t		id;
	pthread_mutex_t	vitals;
	int				amount_philos;
	int				index;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				times_must_eat;
	int				amt_meals;
	long int		last_meal;
	int				r_index;
	int				l_index;
	int				rigth_hand;
	int				left_hand;
	t_env			*e;
}					t_philo;

typedef struct timeval	t_timer;

/*Parsing of arguments and initialization of environnement*/
int			ft_init(t_env *env, int argc, char *args[]);
/*Routine of each philo*/
void		*ft_philo_routine(void *p);
/*Time and meals handlers*/
long int	ft_get_current_time(void);
long int	ft_get_philo_time(long int start);
void		ft_usleep(t_philo *p, int milliseconds);
int			ft_stay_hungry(t_philo *p);
/*Utils for routine*/
void		ft_someone_is_dead(t_philo *p);
int			ft_check_death(t_philo *p);
void		ft_msg(t_philo *philo, char *msg);
int			ft_error_malloc_failed(void);
int			ft_join_threads_error(void);
/*Utils libft*/
long		ft_atoi_overflow(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
int			ft_isdigit(int c);
#endif