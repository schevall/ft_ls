/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:03:01 by schevall          #+#    #+#             */
/*   Updated: 2017/01/09 19:25:29 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	*mem;

	i = 0;
	a = (unsigned char)c;
	mem = (unsigned char *)s;
	while (i < n)
	{
		mem[i] = a;
		i++;
	}
	return (mem);
}
