/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_for_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:54:34 by schevall          #+#    #+#             */
/*   Updated: 2017/02/06 12:17:01 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"
#include <stdio.h>

static void	get_str_size(char *arg, t_param *p)
{
	if (arg != 0)
		p->size_arg = ft_strlen(arg);
	p->size_tot = p->size_arg;
	if (p->prec < p->size_arg && p->width < p->prec)
	{
		p->size_tot = p->prec;
		p->size_arg = p->size_tot;
		if (p->width < p->size_tot)
			p->width = -1;
	}
	else if (p->prec < p->size_arg && p->width >= p->prec && p->prec != -1)
	{
		p->size_tot = p->width;
		p->size_arg = p->prec;
		p->width -= p->prec;
	}
	else if (p->width > p->size_tot)
	{
		p->size_tot = p->width;
		p->width -= p->size_arg;
	}
	else if (p->width <= p->size_arg)
		p->width = -1;
}

static void	fill_with_arg(int i, char *arg, char *str_arg, t_param *p)
{
	int		j;
	int		prec;

	if (p->prec > 0)
		prec = p->prec;
	else
		prec = 2147483647;
	j = 0;
	if (p->prec == 0)
		return ;
	while (str_arg[i] && arg[j] && j < p->size_arg && prec)
	{
		str_arg[i] = arg[j];
		prec--;
		i++;
		j++;
	}
}

static int	apply_str_option(t_param *p, char *str)
{
	int		i;

	i = 0;
	if (p->width > 0 && !p->flags.dash && !p->flags.zero)
	{
		while (p->width-- > 0)
			i++;
	}
	if (p->width > 0 && !p->flags.dash && p->flags.zero)
	{
		while (p->width-- > 0)
			str[i++] = '0';
	}
	return (i);
}

char		*format_string(char *str_arg, va_list ap, t_param *p)
{
	char	*arg;
	int		i;

	arg = va_arg(ap, char*);
	if (p->prec == 0 && !p->flags.zero && p->width < 1)
	{
		str_arg = ft_strnew(0);
		return (str_arg);
	}
	if (arg == NULL && !p->flags.zero)
		arg = "(null)";
	get_str_size(arg, p);
	if ((p->prec > 0 || p->width > 0) && p->flags.zero)
		str_arg = ft_strcnew(p->size_tot, '0');
	else
		str_arg = ft_strcnew(p->size_tot, ' ');
	i = apply_str_option(p, str_arg);
	fill_with_arg(i, arg, str_arg, p);
	return (str_arg);
}
