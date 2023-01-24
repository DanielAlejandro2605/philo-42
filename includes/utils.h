/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:48:05 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/10/21 16:48:05 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

long    ft_atoi_overflow(const char *str);
void	*ft_memcpy(void *dest, void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
int     ft_isdigit(int c);
void	ft_putendl_fd(char *s, int fd);
#endif