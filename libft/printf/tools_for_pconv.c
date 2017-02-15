/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_for_pconv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 13:36:43 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 14:41:16 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		opt_for_p_conv(int i, char *str, t_param *p)
{
	if (p->width > 0 && !p->flags.dash && !p->flags.zero)
		i = p->width;
	i = apply_hash(i, str, p);
	if (p->prec > 0)
	{
		while (p->prec--)
			str[i++] = '0';
	}
	if (p->flags.zero && p->width > 0 && p->prec < 1)
	{
		while (p->width--)
			str[i++] = '0';
	}
	return (i);
}

void	sizer_for_pconv(t_param *p, uintmax_t arg)
{
	if (arg == 0 && !p->prec)
	{
		p->size_arg = 0;
		p->size_tot = (p->width > 2 ? p->width : 2);
		p->width = (p->width > 2 ? (p->width - 2) : 0);
	}
	else
	{
		if ((!p->flags.zero || arg))
			p->size_tot += 2;
		if (p->width > p->size_tot)
			p->size_tot = p->width;
		p->width += -2 - p->size_arg;
		if (p->prec > 0 && p->prec > p->size_arg)
		{
			p->size_tot += (p->prec - p->size_arg);
			p->prec -= p->size_arg;
		}
		else
			p->prec = -1;
	}
}
