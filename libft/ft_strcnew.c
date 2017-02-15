/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 11:47:58 by schevall          #+#    #+#             */
/*   Updated: 2017/01/11 12:25:38 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcnew(size_t n, int c)
{
	char *str;

	if (!(str = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	ft_memset(str, c, n);
	str[n] = '\0';
	return (str);
}
