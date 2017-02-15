/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:51:54 by schevall          #+#    #+#             */
/*   Updated: 2017/02/10 18:53:06 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_error(char *str, int mode, t_ls *st_ls)
{
	int len;

	len = 0;
	if (mode == 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
	if (mode == 1)
	{
		ft_putstr_fd("ls: ", 2);
		if (*str == '\0')
		{
			ft_putstr_fd("fts_open: ", 2);
			ft_putendl_fd(strerror(errno), 2);
			exit(EXIT_FAILURE);
		}
		else
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": ", 2);
			st_ls->error = 1;
		}
		ft_putendl_fd(strerror(errno), 2);
	}
}
