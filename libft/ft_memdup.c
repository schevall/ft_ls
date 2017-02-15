/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 17:26:35 by schevall          #+#    #+#             */
/*   Updated: 2017/01/17 11:29:25 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memdup(const void *s, size_t n)
{
	void	*cpy;

	if (!(cpy = malloc(sizeof(unsigned char) * n)))
		return (NULL);
	ft_memcpy(cpy, s, n);
	return (cpy);
}
