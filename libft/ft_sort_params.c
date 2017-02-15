/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 15:28:15 by schevall          #+#    #+#             */
/*   Updated: 2017/02/01 16:32:29 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_check_if_sorted(int ac, char **tab)
{
	int		i;

	i = 0;
	while (i < ac - 1)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			return (0);
		i++;
	}
	return (1);
}

char		**ft_sort_params(int ac, char **tab)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < ac - 1)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
		}
		i++;
	}
	if (!ft_check_if_sorted(ac, tab))
		ft_sort_params(ac, tab);
	return (tab);
}
