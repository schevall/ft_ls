/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 12:21:42 by schevall          #+#    #+#             */
/*   Updated: 2017/01/06 11:18:26 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int nb)
{
	size_t	i;
	size_t	len;
	char	*res;

	i = 0;
	len = (nb < 0) ? ft_nbrlen(nb) + 1 : ft_nbrlen(nb);
	if (!(res = ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (len > 0)
	{
		if (nb == -2147483648)
			return (ft_strcpy(res, "-2147483648"));
		if (nb < 0)
		{
			nb = -nb;
			res[i++] = '-';
			len--;
		}
		res[i++] = (nb / ft_power(10, len - 1)) + '0';
		nb = nb % (ft_power(10, len-- - 1));
	}
	res[i] = '\0';
	return (res);
}
