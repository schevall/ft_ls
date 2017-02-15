/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_for_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 14:42:59 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 13:04:57 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static void			get_char_size(t_param *p)
{
	int				size_arg;
	int				size_tot;

	size_arg = 1;
	size_tot = size_arg;
	if (p->width > size_tot)
		size_tot = p->width;
	else
		p->width = -1;
	p->size_arg = size_arg;
	p->size_tot = size_tot;
}

static int			apply_char_option(t_param *p, char *str, unsigned char arg)
{
	int				i;

	i = 0;
	if (p->width > 0 && !p->flags.dash && !p->flags.zero)
		i = p->width - 1;
	else if (p->width > 0 && !p->flags.dash && p->flags.zero)
	{
		while (p->width-- > 1)
			str[i++] = '0';
	}
	if (p->prec > 0 && i < p->size_tot && arg != 0)
	{
		while (p->prec-- > 1)
			str[i++] = '0';
	}
	return (i);
}

static char			*format_char_spec(char *str, unsigned char arg,
													t_param *p, int tok)
{
	int i;

	if (tok == 1)
	{
		str = ft_strcnew(p->size_tot, ' ');
		str[p->size_tot - 1] = arg;
	}
	if (tok == 2)
	{
		str = ft_strcnew(p->width, '0');
		p->size_tot = p->width;
		str[p->width - 1] = arg;
	}
	if (tok == 3)
	{
		create_str_arg(&str, p);
		i = apply_char_option(p, str, arg);
		str[i] = arg;
	}
	return (str);
}

char				*format_char(char *str_arg, va_list ap, t_param *p)
{
	unsigned char	arg;

	if (p->conv == 'c')
		arg = (unsigned char)va_arg(ap, int);
	else if (p->conv)
		arg = p->conv;
	else
	{
		str_arg = ft_strdup("\0");
		p->size_tot = 0;
		return (str_arg);
	}
	get_char_size(p);
	if (p->prec > 0 && !p->flags.zero)
		str_arg = format_char_spec(str_arg, arg, p, 1);
	else if (!p->prec && p->flags.zero && p->width > 0)
		str_arg = format_char_spec(str_arg, arg, p, 2);
	else
		str_arg = format_char_spec(str_arg, arg, p, 3);
	return (str_arg);
}
