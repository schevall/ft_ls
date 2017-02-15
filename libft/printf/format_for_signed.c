/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_for_signed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:26:20 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 13:22:34 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static int	nbr_size(intmax_t arg)
{
	size_t	len;

	len = 0;
	if (arg == 0)
		return (1);
	while (arg)
	{
		arg /= 10;
		len++;
	}
	return (len);
}

static void	get_signed_size(intmax_t arg, t_param *p)
{
	p->size_arg = nbr_size(arg);
	p->size_tot = p->size_arg;
	if (p->prec > p->size_arg)
	{
		p->size_tot = p->prec;
		p->prec -= p->size_arg;
	}
	else if (p->prec != 0)
		p->prec = -1;
	if (((p->flags.spaced || p->flags.plus) && arg >= 0) || arg < 0)
		p->size_tot++;
	if (p->width > p->size_tot)
	{
		p->size_tot = p->width;
		p->width += -p->size_arg - (p->prec != -1 ? p->prec : 0);
		if (((p->flags.spaced || p->flags.plus) && arg >= 0) || arg < 0)
			p->width--;
	}
	else
		p->width = -1;
}

static void	fill_with_arg(int i, intmax_t arg, char *str_arg, t_param *params)
{
	int			pw;

	if (!arg && !params->prec && params->width < 1)
	{
		params->size_tot = 0;
		return ;
	}
	else if (!arg && !params->prec && params->width > 0)
	{
		params->size_tot = ft_strlen(str_arg);
		return ;
	}
	pw = params->size_arg - 1;
	while (arg || params->size_arg)
	{
		str_arg[i++] = '0' + (arg / ft_power(10, (pw)));
		arg = arg - ft_power(10, pw) * (arg / ft_power(10, pw));
		params->size_arg--;
		pw--;
	}
}

static int	apply_signed_option(intmax_t *arg, char *str, t_param *p)
{
	int			i;

	i = 0;
	if (*arg == 0 && !p->prec)
		return (width_for_zero(i, p));
	if (p->width > 0 && !p->flags.dash && !p->flags.zero)
		i = p->width;
	if (*arg >= 0 && p->flags.plus)
		str[i++] = '+';
	else if (*arg >= 0 && p->flags.spaced)
		str[i++] = ' ';
	else if (*arg < 0)
	{
		str[i++] = '-';
		*arg *= -1;
	}
	if (p->flags.zero && p->width > 0)
		i = put_zeros_for_signed(str, i, p, 1);
	else if (p->prec > 0)
		i = put_zeros_for_signed(str, i, p, 2);
	return (i);
}

char		*format_signed(char *str_arg, va_list ap, t_param *params)
{
	intmax_t	arg;
	int			start_index;

	arg = get_signed_arg(ap, params);
	get_signed_size(arg, params);
	create_str_arg(&str_arg, params);
	start_index = apply_signed_option(&arg, str_arg, params);
	fill_with_arg(start_index, arg, str_arg, params);
	return (str_arg);
}
