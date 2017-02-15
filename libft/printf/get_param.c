/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:39:23 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 13:07:41 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static void	get_flag(const char **format, t_param *params)
{
	while (is_flag(**format) && **format)
	{
		if (**format == '#')
			params->flags.hash = 1;
		else if (**format == '-')
			params->flags.dash = 1;
		else if (**format == '+')
			params->flags.plus = 1;
		else if (**format == ' ')
			params->flags.spaced = 1;
		else if (**format == '0')
			params->flags.zero = 1;
		if (**format)
			(*format)++;
	}
}

static void	get_width(const char **format, va_list ap, t_param *params)
{
	if (ft_isdigit(**format))
	{
		params->width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	else if (**format == '*')
	{
		params->width = va_arg(ap, int);
		(*format)++;
		if (params->width < 0)
		{
			params->width *= -1;
			params->flags.dash = 1;
		}
	}
}

static void	get_prec(const char **format, va_list ap, t_param *params)
{
	(*format)++;
	if (ft_isdigit(**format))
	{
		params->prec = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	else if (**format == '*')
	{
		params->prec = va_arg(ap, int);
		(*format)++;
		if (params->prec < 0)
			params->prec = -1;
	}
	else
		params->prec = 0;
}

static void	get_length(const char **format, t_param *params)
{
	while (is_length(**format) && **format)
	{
		if (**format == 'l')
			params->length.l++;
		else if (**format == 'j')
			params->length.j++;
		else if (**format == 'h')
			params->length.h++;
		else if (**format == 'z')
			params->length.z++;
		if (**format)
			(*format)++;
	}
}

void		get_params(const char **format, va_list ap, t_param *params)
{
	while ((is_flag(**format) || is_length(**format) || ft_isdigit(**format)
			|| **format == '*' || **format == '.') && **format)
	{
		if (is_flag(**format))
			get_flag(format, params);
		else if (ft_isdigit(**format) || **format == '*')
			get_width(format, ap, params);
		else if (**format == '.')
			get_prec(format, ap, params);
		else if (is_length(**format))
			get_length(format, params);
	}
	params->conv = **format;
	if (**format)
		(*format)++;
}
