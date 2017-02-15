/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_from_ap_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:19:29 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 13:07:27 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

intmax_t	get_signed_arg(va_list ap, t_param *params)
{
	intmax_t arg;

	if (params->length.l >= 2)
		arg = (intmax_t)va_arg(ap, long long);
	else if (params->length.l == 1 || params->conv == 'D')
		arg = (intmax_t)va_arg(ap, long);
	else if (params->length.z >= 1)
		arg = (intmax_t)va_arg(ap, ssize_t);
	else if (params->length.j >= 1)
		arg = va_arg(ap, intmax_t);
	else if (params->length.h >= 2)
		arg = (intmax_t)(char)va_arg(ap, int);
	else if (params->length.h == 1)
		arg = (intmax_t)(short)va_arg(ap, int);
	else
		arg = (intmax_t)va_arg(ap, int);
	return (arg);
}

intmax_t	get_unsigned_arg(va_list ap, t_param *params)
{
	uintmax_t arg;

	if (params->length.l >= 2)
		arg = (uintmax_t)va_arg(ap, unsigned long long);
	else if (params->length.l == 1 || params->conv == 'U'
			|| params->conv == 'O')
		arg = (uintmax_t)va_arg(ap, unsigned long);
	else if (params->length.z >= 1 || params->conv == 'p')
		arg = (uintmax_t)va_arg(ap, size_t);
	else if (params->length.j >= 1)
		arg = va_arg(ap, uintmax_t);
	else if (params->length.h >= 2)
		arg = (uintmax_t)(unsigned char)va_arg(ap, unsigned int);
	else if (params->length.h == 1)
		arg = (uintmax_t)(unsigned short)va_arg(ap, unsigned int);
	else
		arg = (uintmax_t)va_arg(ap, unsigned int);
	return (arg);
}
