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

#include "../includes/philo.h"

void    ft_error_args(void)
{
    printf("Invalid use of the program.\n");
    exit(1);
}

void    ft_create_threads_error(void)
{
    printf("Error creating the threads.\n");
    exit(1);
}