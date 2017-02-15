/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:55:45 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 16:18:36 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int		apply_hash(int i, char *str, t_param *p)
{
	str[i++] = '0';
	if (is_octal(p->conv) && p->prec > 0)
		p->prec--;
	if (p->conv == 'x' || p->conv == 'p')
		str[i++] = 'x';
	if (p->conv == 'X')
		str[i++] = 'X';
	return (i);
}

void	sizer_precz_argz(t_param *p)
{
	p->size_arg = 0;
	if (p->width < 1)
		p->size_tot = 0;
	if (is_octal(p->conv) && p->flags.hash)
	{
		p->size_arg = 1;
		p->size_tot = 1 + (p->width > 0 ? p->width : 0);
	}
}

void	width_hashed(t_param *p, uintmax_t arg)
{
	if (is_hexa(p->conv) && p->flags.hash && arg)
		p->width -= 2;
	if (is_octal(p->conv) && p->flags.hash && arg)
		p->width--;
}

void	case_precz_argz(t_param *p)
{
	if (is_hexa(p->conv) || p->conv == 'u' || (is_octal(p->conv)
				&& !p->flags.hash))
	{
		p->size_arg = 0;
		p->size_tot = 0;
	}
}

int		apply_zero(t_param *p, int i, char *str, uintmax_t arg)
{
	width_hashed(p, arg);
	while (p->width--)
		str[i++] = '0';
	return (i);
}
