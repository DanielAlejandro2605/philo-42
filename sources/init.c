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

# include "../includes/philo.h"

int	ft_init(t_env *env, char *args[])
{
	env->amount_philos = ft_atoi(args[0]);
	env->time_to_die = ft_atoi(args[1]);
	env->time_to_eat = ft_atoi(args[2]);
	env->time_to_sleep = ft_atoi(args[3]);
	if (args[4])
		env->times_must_eat = ft_atoi(args[4]);
	else
		env->times_must_eat = 0;
	env->guest_philos = ft_set_dinner_table(env->amount_philos);
	return (0);
}

t_list	*ft_set_dinner_table(int amt_philos)
{
	t_list	*guest_table;
	int		i;

	guest_table = NULL;
	// i = 0;
	// while (i < amt_philos)
	// {
	// 	ft_add_philo_to_table();
	// 	ft_add_forks_to_table();
	// 	i++;
	// }
	(void)amt_philos;
	i = 1;
	ft_init_philo(&guest_table, i);
	t_fork *fork = (t_fork*)guest_table->item;
	printf("here : %d\n", fork->index);
	return (guest_table);
}

void	ft_init_philo(t_list **begin_lst, int flag_item)
{
	t_fork	*new_fork;

	if (flag_item == 1)
	{
		new_fork = (t_fork *)malloc(sizeof(t_fork));
		new_fork->index = flag_item;
		new_fork->forks = flag_item;
		printf("%d\n", new_fork->index);
		ft_push(begin_lst, (void *)new_fork, sizeof(t_fork));
	}
}

void	ft_push(t_list **begin_lst, void *data, size_t data_size)
{
	int	i;

	if (*begin_lst == NULL) {
        t_list	*new_fork = (t_list*)malloc(sizeof(t_list));
		new_fork->item  = malloc(data_size);
		i = 0;
		while (i < (int)data_size)
		{
			*(char *)(new_fork->item + i) = *(char *)(data + i);
			i++;
		}
		new_fork->next = new_fork->prev = new_fork;
        *begin_lst = new_fork;
        return;
	}

	/* Find last node */
    // t_list *last = (*begin_lst)->prev;
  
    // // Create Node dynamically
   	// t_list	*new_philo = (*t_list)malloc(sizeof(t_list));
    // new_philo->item  = malloc(data_size);
  
    // // Start is going to be next of new_node
    // new_node->next = *start;
  
    // // Make new node previous of start
    // (*start)->prev = new_node;
  
    // // Make last previous of new node
    // new_node->prev = last;
  
    // // Make new node next of old last
    // last->next = new_node;
}





