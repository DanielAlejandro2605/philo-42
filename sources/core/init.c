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

static t_forks	ft_define_forks(int	amt_philos, int idx_philo)
{
	t_forks	f_philo;

	if (idx_philo == 1)
	{
		f_philo.l = amt_philos - 1;
		f_philo.r = 0;
		if (f_philo.l == f_philo.r)
		{
			f_philo.l = -1;
		}
	}
	else
	{
		f_philo.l = idx_philo - 2;
		f_philo.r = idx_philo - 1;
	}
	return (f_philo);
}

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
		{
			return (NULL);
		}
		philos[i]->index = i + 1;
		philos[i]->forks_idx = ft_define_forks(env->amount_philos, i + 1);
		philos[i]->e = env;
		i++;
	}
	philos[i] = NULL;
	return (philos);
}
// static int	*ft_create_forks(int amt_forks)
// {
// 	int	*forks;
// 	int	i;

// 	forks = (int *)malloc(sizeof(int) * amt_forks);
// 	if (!forks)
// 		return (NULL);
// 	i = 0;
// 	while (i < amt_forks)
// 	{
// 		forks[i] = i + 1;
// 		i++;
// 	}
// 	return (forks);
// }

// static t_philo	*ft_malloc_philo(t_env *env, int index)
// {
// 	t_philo	*new_philo;

// 	new_philo = (t_philo *)malloc(sizeof(t_philo));
// 	if (!new_philo)
// 		return (NULL);
// 	new_philo->index = index + 1;
// 	new_philo->time_to_die = env->time_to_die;
// 	new_philo->t_eat = env->t_eat;
// 	new_philo->t_sleep = env->t_sleep;
// 	if (env->times_must_eat)
// 		new_philo->times_must_eat = env->times_must_eat;
// 	else
// 		new_philo->times_must_eat = 0;
// 	new_philo->forks = NULL;
// 	return (new_philo);
// }

// static t_list	*ft_malloc_philo_node(size_t data_size)
// {
// 	t_list	*new_philo_node;

// 	new_philo_node = (t_list *)malloc(sizeof(t_list));
// 	if (!new_philo_node)
// 		return (NULL);
// 	new_philo_node->item = malloc(data_size);
// 	if (!new_philo_node->item)
// 	{
// 		free(new_philo_node);
// 		return (NULL);
// 	}
// 	return (new_philo_node);
// }

// static int	ft_add_philo_table(t_list **lst, void *data, size_t data_size)
// {
// 	t_list	*new_philo_node;
// 	t_list	*last;

// 	new_philo_node = ft_malloc_philo_node(data_size);
// 	if (!new_philo_node)
// 	{
// 		//ft_free_list(lst);
// 		return (1);
// 	}
// 	new_philo_node->item = ft_memcpy(new_philo_node->item, data, data_size);
// 	if (*lst == NULL)
// 	{
// 		new_philo_node->next = new_philo_node;
// 		new_philo_node->prev = new_philo_node;
// 		*lst = new_philo_node;
// 		return (0);
// 	}
// 	last = (*lst)->prev;
// 	new_philo_node->next = *lst;
// 	(*lst)->prev = new_philo_node;
// 	new_philo_node->prev = last;
// 	last->next = new_philo_node;
// 	return (0);
// }

// t_list	*ft_set_dinner_table(t_env *env, int **forks)
// {
// 	t_list	*lst_philos;
// 	t_philo	*philo_aux;
// 	int		i;

// 	lst_philos = NULL;
// 	*forks = ft_create_forks(env->amount_philos);
// 	i = 0;
// 	while (i < env->amount_philos)
// 	{
// 		philo_aux = ft_malloc_philo(env, i);
// 		ft_add_philo_table(&lst_philos, (void *)philo_aux, sizeof(t_philo));
// 		free(philo_aux);
// 		i++;
// 	}
// 	return (lst_philos);
// }
