/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:01:51 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/11/14 11:01:51 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char	*cpy_src;
	unsigned char	*cpy_dest;
	size_t			i;

	if (!dest)
		return (NULL);
	i = 0;
	cpy_src = (unsigned char *)src;
	cpy_dest = (unsigned char *)dest;
	while (i < n)
	{
		*(cpy_dest + i) = *(cpy_src + i);
		i++;
	}
	return (dest);
}