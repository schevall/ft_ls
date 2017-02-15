/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_for_signed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:30:41 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 14:39:39 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int		width_for_zero(int i, t_param *p)
{
	if (p->width > 0)
		i = p->width;
	return (i);
}

int		put_zeros_for_signed(char *str, int i, t_param *p, int tok)
{
	if (tok == 1)
	{
		while (p->width--)
			str[i++] = '0';
	}
	if (tok == 2)
	{
		while (p->prec--)
			str[i++] = '0';
	}
	return (i);
}
