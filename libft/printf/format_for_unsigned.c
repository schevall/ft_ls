/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_for_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:57:15 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 14:21:25 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static void	sizer_aux_for_prec(t_param *p, uintmax_t arg)
{
	p->size_tot = p->prec;
	if (arg)
		p->size_tot -= p->flags.hash * (is_octal(p->conv));
	p->prec -= p->size_arg;
}

static void	get_unsigned_size(uintmax_t arg, t_param *p, int base)
{
	p->size_arg = ft_nbrlen_base(arg, base);
	p->size_tot = p->size_arg;
	if (p->conv == 'p')
		return (sizer_for_pconv(p, arg));
	if (p->prec > p->size_arg)
		sizer_aux_for_prec(p, arg);
	else if (p->prec != 0)
		p->prec = -1;
	if (p->flags.hash && is_hexa(p->conv) && arg && !p->flags.zero)
		p->size_tot += 2;
	if (p->flags.hash && is_octal(p->conv) && arg && !p->flags.zero)
		p->size_tot += 1;
	if (p->width > p->size_tot)
	{
		p->size_tot = p->width;
		p->width += -p->size_arg - (p->prec != -1 ? p->prec : 0);
	}
	else
		p->width = -1;
	if (arg == 0 && p->prec == 0 && !(p->conv == 'p'))
		sizer_precz_argz(p);
}

static void	fill_with_arg(int i, uintmax_t arg, char *str, t_param *p)
{
	int		pw;
	char	base_str[16];

	pw = p->size_arg - 1;
	ft_strncpy(base_str, "0123456789abcdef", p->base);
	if (!p->prec && !arg && is_oct_or_hex(p->conv) && !p->flags.hash)
		p->size_arg = 0;
	while (arg || p->size_arg)
	{
		str[i++] = base_str[arg / ft_power(p->base, pw)];
		arg = arg - ft_power(p->base, pw) * (arg / ft_power(p->base, pw));
		pw--;
		p->size_arg--;
	}
	if (p->conv == 'p' && arg == 0 && (int)ft_strlen(str) < p->size_tot)
	{
		if (p->prec == 0)
		{
			p->size_tot = 2;
			return ;
		}
		str[i] = '0';
	}
	if (p->conv == 'X')
		ft_strupcase(str);
}

static int	apply_unsigned_option(uintmax_t arg, char *str, t_param *p)
{
	int		i;

	i = 0;
	if (p->conv == 'p')
		return (opt_for_p_conv(i, str, p));
	if (arg == 0 && !p->prec && p->width > 0 && !p->flags.dash)
		return (width_for_zero(i, p));
	if (p->width > 0 && !p->flags.dash && !p->flags.zero)
	{
		width_hashed(p, arg);
		i = p->width;
	}
	if ((p->flags.hash && arg))
		i = apply_hash(i, str, p);
	else if (!arg && !p->prec && p->width < 1)
		case_precz_argz(p);
	if (p->prec > 0)
	{
		while (p->prec--)
			str[i++] = '0';
	}
	if (p->flags.zero && p->width > 0 && p->prec < 1)
		i = apply_zero(p, i, str, arg);
	return (i);
}

char		*format_unsign(char *str, va_list ap, t_param *params)
{
	uintmax_t	arg;
	int			start_index;

	arg = get_unsigned_arg(ap, params);
	params->base = get_base(params);
	get_unsigned_size(arg, params, params->base);
	create_str_arg(&str, params);
	start_index = apply_unsigned_option(arg, str, params);
	fill_with_arg(start_index, arg, str, params);
	return (str);
}
