/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:25:22 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/11/07 09:25:22 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_error_args(void)
{
	printf("Invalid use of the program.\n");
	return (1);
}

int	ft_error_malloc_failed(void)
{
	printf("Malloc failed.\n");
	return (1);
}

int	ft_create_threads_error(void)
{
	printf("Error creating the threads.\n");
	return (1);
}

int	ft_join_threads_error(void)
{
	printf("Error joining the threads.\n");
	return (1);
}