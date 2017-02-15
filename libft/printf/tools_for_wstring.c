/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_for_wstring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:04:24 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 14:41:24 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int		get_wchar_size(wint_t arg)
{
	if (arg >= 0 && arg <= 0x7f)
		return (1);
	else if (arg >= 0x80 && arg <= 0x7ff)
		return (2);
	else if (arg >= 0x800 && arg <= 0xd7ff)
		return (3);
	else if (arg >= 0xe000 && arg <= 0xffff)
		return (3);
	else if (arg >= 0x10000 && arg <= 0x10ffff)
		return (4);
	else
		return (0);
}

char	*spec_for_wstring(char *str_arg, t_param *p, int tok)
{
	if (tok == 1)
	{
		str_arg = ft_strnew(6);
		str_arg = ft_strcpy(str_arg, "(null)");
		p->size_tot = 6;
	}
	else if (tok == 2)
	{
		if (p->width > 0 && p->flags.zero)
		{
			str_arg = ft_strcnew(p->width, '0');
			p->size_tot = p->width;
		}
		else if (p->width > 0 && !p->flags.zero)
		{
			str_arg = ft_strcnew(p->width, ' ');
			p->size_tot = p->width;
		}
		else
		{
			str_arg = ft_strnew(1);
			p->size_tot = 0;
		}
	}
	return (str_arg);
}
