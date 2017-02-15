/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:32:43 by schevall          #+#    #+#             */
/*   Updated: 2017/01/26 11:47:33 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static void	check_params(t_param *p)
{
	if (p->flags.dash && p->width < 1)
		p->flags.dash = 0;
	if (p->flags.zero && (p->prec >= 0 || p->width < 1) && (p->conv == 'd' ||
	p->conv == 'D' || p->conv == 'u' || p->conv == 'U' || p->conv == 'i' ||
	is_oct_or_hex(p->conv)))
		p->flags.zero = 0;
	if (p->flags.zero && p->flags.dash)
		p->flags.zero = 0;
	if (p->flags.plus && p->flags.spaced)
		p->flags.spaced = 0;
	if (p->prec >= p->width)
	{
		if (p->conv == 's' || p->conv == 'S' || p->conv == 'c'
				|| p->conv == 'C')
			return ;
		p->width = -1;
	}
	if (p->conv == 'p')
		p->flags.hash = 1;
}

static int	format_arg(const char **format, char **s, va_list ap,
															t_param *params)
{
	int		size;

	re_init_params(params);
	get_params(format, ap, params);
	check_params(params);
	size = format_tree(s, ap, params);
	params->size_s_tot += size;
	return (size);
}

static int	unformated_part(const char *format, char **s, t_param *params)
{
	int		i;
	char	*tmp;

	tmp = *s;
	i = 0;
	while (*(format + i) && *(format + i) != '%')
		i++;
	if (!(*s = ft_strnjoin(*s, params->size_s_tot, format, i)))
		return (-1);
	params->size_s_tot += i;
	free(tmp);
	return (i);
}

static int	buffering(const char *format, va_list ap, char **s, t_param *params)
{
	int		size;
	int		total;

	total = 0;
	size = 0;
	while (*format)
	{
		if (*format != '%')
		{
			if ((size = unformated_part(format, s, params)) == -1)
				return (-1);
			format += size;
		}
		else
		{
			format++;
			if ((size = format_arg(&format, s, ap, params)) == -1)
				return (-1);
		}
		total += size;
	}
	return (total);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	char	*s;
	int		total;
	t_param params;

	init_params(&params);
	va_start(ap, format);
	if (!(s = ft_strnew(1)))
		return (-1);
	total = buffering(format, ap, &s, &params);
	if (total == -1)
		return (-1);
	if (total == 0)
	{
		total = ft_strlen(s);
		write(1, s, total);
	}
	else
		write(1, s, total);
	free(s);
	va_end(ap);
	return (total);
}
