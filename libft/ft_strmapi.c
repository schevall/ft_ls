/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:06:15 by schevall          #+#    #+#             */
/*   Updated: 2016/11/22 16:02:38 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		cpy[i] = f(i, s[i]);
		i++;
	}
	return (cpy);
}
