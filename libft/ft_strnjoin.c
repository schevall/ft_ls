/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 13:58:02 by schevall          #+#    #+#             */
/*   Updated: 2017/01/20 15:02:26 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, int n1, char const *s2, int n2)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(new = ft_strnew(n1 + n2 + 1)))
		return (NULL);
	while (i < n1)
	{
		new[i] = s1[i];
		i++;
	}
	while (i < n1 + n2)
	{
		new[i] = s2[j];
		j++;
		i++;
	}
	return (new);
}
