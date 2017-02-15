/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_conv_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:17:30 by schevall          #+#    #+#             */
/*   Updated: 2017/02/06 11:23:07 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int		is_signed_conv(int conv)
{
	if (conv == 'd' || conv == 'D' || conv == 'i')
		return (1);
	return (0);
}

int		is_unsigned_conv(int conv)
{
	if (conv == 'o' || conv == 'O' || conv == 'u' || conv == 'b')
		return (1);
	else if (conv == 'U' || conv == 'x' || conv == 'X' || conv == 'p')
		return (1);
	else
		return (0);
}

int		is_hexa(int conv)
{
	if (conv == 'x' || conv == 'X' || conv == 'p')
		return (1);
	return (0);
}

int		is_octal(int conv)
{
	if (conv == 'o' || conv == 'O')
		return (1);
	return (0);
}

int		is_oct_or_hex(int conv)
{
	if (is_hexa(conv) || is_octal(conv))
		return (1);
	return (0);
}
