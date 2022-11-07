/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 09:29:14 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/10/21 09:29:14 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// static void	ft_dinner(t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	while (i < env->amount_philos)
// 	{

// 	}
// }

int	main(int argc, char *argv[])
{
	t_env	env;
	
	if (argc < 5 || argc > 6)
		ft_error_args();
	if(ft_init(&env, argv + 1))
		ft_create_threads_error();
	ft_free(&env);
}
