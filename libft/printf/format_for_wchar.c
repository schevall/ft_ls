/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_for_wchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 12:29:43 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 14:36:20 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static void	wchar_sizer(wint_t arg, t_param *p)
{
	if (arg >= 0 && arg <= 0x7f)
		p->size_arg = 1;
	else if (arg >= 0x80 && arg <= 0x7ff)
		p->size_arg = 2;
	else if (arg >= 0x800 && arg <= 0xd7ff)
		p->size_arg = 3;
	else if (arg >= 0xe000 && arg <= 0xffff)
		p->size_arg = 3;
	else if (arg >= 0x10000 && arg <= 0x10ffff)
		p->size_arg = 4;
	else
		p->size_arg = 0;
	if (p->width > p->size_arg && p->size_arg == 1)
		p->size_tot = p->width;
	else if (p->width > p->size_arg && p->size_arg > 1)
	{
		p->size_tot = p->width;
		p->width -= p->size_arg - 1;
	}
	else
	{
		p->size_tot = p->size_arg;
		p->width = -1;
	}
}

static int	apply_wchar_option(t_param *p, char *str)
{
	int i;

	i = 0;
	if (p->width > 0 && !p->flags.dash && !p->flags.zero)
	{
		while (p->width-- > 1)
			i++;
	}
	if (p->width > 0 && !p->flags.dash && p->flags.zero)
	{
		while (p->width-- > 1)
			str[i++] = '0';
	}
	return (i);
}

char		*fill_with_unicode(int i, wint_t arg, char *str_arg)
{
	if (arg >= 0 && arg <= 127)
		str_arg[i++] = (char)arg;
	else if (arg >= 128 && arg <= 2047)
	{
		str_arg[i++] = (char)(0xc0 | (arg >> 6));
		str_arg[i++] = (char)(0x80 | (arg & 0x3f));
	}
	else if ((arg >= 2048 && arg <= 55295) || (arg >= 57344 && arg <= 65535))
	{
		str_arg[i++] = (char)(0xe0 | ((arg >> 12) & 0xf));
		str_arg[i++] = (char)(0x80 | ((arg >> 6) & 0x3f));
		str_arg[i++] = (char)(0x80 | (arg & 0x3f));
	}
	else if (arg >= 65536 && arg <= 1114111)
	{
		str_arg[i++] = (char)(0xf0 | ((arg >> 18) & 0x7));
		str_arg[i++] = (char)(0x80 | ((arg >> 12) & 0x3f));
		str_arg[i++] = (char)(0x80 | ((arg >> 6) & 0x3f));
		str_arg[i++] = (char)(0x80 | (arg & 0x3f));
	}
	return (str_arg);
}

char		*format_wchar(char *str_arg, va_list ap, t_param *params)
{
	wint_t	arg;
	int		start_index;

	arg = va_arg(ap, wint_t);
	wchar_sizer(arg, params);
	if (!params->size_arg)
		return (NULL);
	str_arg = ft_strcnew(params->size_tot, ' ');
	start_index = apply_wchar_option(params, str_arg);
	str_arg = fill_with_unicode(start_index, arg, str_arg);
	return (str_arg);
}
