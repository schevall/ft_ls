/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_for_wstring.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:26:19 by schevall          #+#    #+#             */
/*   Updated: 2017/01/26 12:22:05 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static int	get_wstr_size(wchar_t *arg, t_param *p)
{
	int prec;

	if (p->prec < 0)
		p->prec = 2147483647;
	prec = p->prec;
	while (*arg && prec > 0)
	{
		if (!(p->size_arg = get_wchar_size(*arg)))
		{
			p->size_tot = -1;
			return (-1);
		}
		if (prec - p->size_arg >= 0)
			p->size_tot += p->size_arg;
		prec -= p->size_arg;
		arg++;
	}
	if (p->width > p->size_tot)
	{
		p->width -= p->size_tot;
		return (p->size_tot + p->width);
	}
	else
		p->width = -1;
	return (p->size_tot);
}

static int	apply_wstring_option(t_param *params)
{
	int i;

	i = 0;
	if (params->width > 0 && !params->flags.dash)
	{
		while (params->width-- > 0)
			i++;
	}
	return (i);
}

static char	*fill_with_unicode(int *i, wint_t arg, char *str_arg)
{
	if (arg >= 0 && arg <= 127)
		str_arg[(*i)++] = (char)arg;
	else if (arg >= 128 && arg <= 2047)
	{
		str_arg[(*i)++] = (char)(0xc0 | (arg >> 6));
		str_arg[(*i)++] = (char)(0x80 | (arg & 0x3f));
	}
	else if ((arg >= 2048 && arg <= 55295) || (arg >= 57344 && arg <= 65535))
	{
		str_arg[(*i)++] = (char)(0xe0 | ((arg >> 12) & 0xf));
		str_arg[(*i)++] = (char)(0x80 | ((arg >> 6) & 0x3f));
		str_arg[(*i)++] = (char)(0x80 | (arg & 0x3f));
	}
	else if (arg >= 65536 && arg <= 1114111)
	{
		str_arg[(*i)++] = (char)(0xf0 | ((arg >> 18) & 0x7));
		str_arg[(*i)++] = (char)(0x80 | ((arg >> 12) & 0x3f));
		str_arg[(*i)++] = (char)(0x80 | ((arg >> 6) & 0x3f));
		str_arg[(*i)++] = (char)(0x80 | (arg & 0x3f));
	}
	return (str_arg);
}

static char	*fill_with_arg(t_param *p, wchar_t *arg, char *str)
{
	int i;

	i = 0;
	if ((p->size_tot = get_wstr_size(arg, p)) == -1)
		return (NULL);
	if (p->flags.zero)
		str = ft_strcnew(p->size_tot, '0');
	else
		str = ft_strcnew(p->size_tot, ' ');
	i = apply_wstring_option(p);
	while (*arg && p->prec > 0)
	{
		p->size_arg = get_wchar_size(*arg);
		if (p->size_arg <= p->prec)
			fill_with_unicode(&i, *arg, str);
		p->prec -= p->size_arg;
		arg++;
	}
	return (str);
}

char		*format_wstring(char *str, va_list ap, t_param *p)
{
	wchar_t	*arg;

	arg = va_arg(ap, wchar_t*);
	if (arg == NULL)
		return (spec_for_wstring(str, p, 1));
	else if (p->prec == 0)
		return (spec_for_wstring(str, p, 2));
	else
		str = fill_with_arg(p, arg, str);
	return (str);
}
