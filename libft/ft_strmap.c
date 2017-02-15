/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:06:09 by schevall          #+#    #+#             */
/*   Updated: 2016/11/21 12:47:45 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmap(char const *s, char (*f)(char))
{
	size_t			len;
	char			*cpy;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	if (!(cpy = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (s[i] && f)
	{
		cpy[i] = f(s[i]);
		i++;
	}
	return (cpy);
}
