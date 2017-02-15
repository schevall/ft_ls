/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbrlen_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 14:00:17 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 16:27:15 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int		get_base(t_param *params)
{
	if (params->conv == 'u' || params->conv == 'U')
		return (10);
	if (params->conv == 'x' || params->conv == 'X' || params->conv == 'p')
		return (16);
	if (params->conv == 'o' || params->conv == 'O')
		return (8);
	return (2);
}

int		ft_nbrlen_base(uintmax_t arg, int base)
{
	int len;

	len = 0;
	if (arg == 0)
		return (1);
	while (arg)
	{
		arg /= base;
		len++;
	}
	return (len);
}
