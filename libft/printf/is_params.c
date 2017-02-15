/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:41:42 by schevall          #+#    #+#             */
/*   Updated: 2017/01/24 14:45:09 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int		is_flag(char c)
{
	if (ft_strchr("+-# 0", c))
		return (1);
	return (0);
}

int		is_length(char c)
{
	if (ft_strchr("ljhz", c))
		return (1);
	return (0);
}

void	init_params(t_param *params)
{
	params->flags.hash = 0;
	params->flags.dash = 0;
	params->flags.plus = 0;
	params->flags.spaced = 0;
	params->flags.zero = 0;
	params->length.l = 0;
	params->length.j = 0;
	params->length.h = 0;
	params->length.z = 0;
	params->conv = 0;
	params->width = -1;
	params->prec = -1;
	params->size_arg = 0;
	params->size_tot = 0;
	params->size_s_tot = 0;
	params->base = 0;
}

void	re_init_params(t_param *params)
{
	params->flags.hash = 0;
	params->flags.dash = 0;
	params->flags.plus = 0;
	params->flags.spaced = 0;
	params->flags.zero = 0;
	params->length.l = 0;
	params->length.j = 0;
	params->length.h = 0;
	params->length.z = 0;
	params->conv = 0;
	params->width = -1;
	params->prec = -1;
	params->size_arg = 0;
	params->size_tot = 0;
	params->base = 0;
}
