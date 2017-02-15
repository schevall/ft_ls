/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 12:39:20 by schevall          #+#    #+#             */
/*   Updated: 2017/02/11 19:17:47 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	check_overide(char c, t_ls *st_ls)
{
	if (c)
	{
		if (st_ls->opt['1'] && c == 'l')
			st_ls->opt['1'] = 0;
		else if (st_ls->opt['l'] && c == '1')
			st_ls->opt['l'] = 0;
		else if (st_ls->opt['c'] && c == 'u')
			st_ls->opt['c'] = 0;
		else if (st_ls->opt['u'] && c == 'c')
			st_ls->opt['u'] = 0;
	}
	if (st_ls->opt['f'])
	{
		st_ls->opt['a'] = 1;
		st_ls->opt['r'] = 0;
	}
	if (st_ls->opt['t'] && st_ls->opt['S'])
		st_ls->opt['t'] = 0;
}

static	int	is_opt(char c)
{
	char	*base_opt;
	int		i;

	i = 0;
	base_opt = OPTION_LIST;
	while (base_opt[i])
	{
		if (base_opt[i++] == c)
			return (1);
	}
	return (0);
}

static void	opt_filler(char *av, t_ls *st_ls)
{
	av++;
	while (*av)
	{
		if (is_opt(*av))
		{
			check_overide(*av, st_ls);
			st_ls->opt[(int)*av] = *av;
		}
		else
		{
			ft_putstr_fd(ILLEGAL, 2);
			ft_putchar_fd(*av, 2);
			ft_putstr_fd("\n", 2);
			ft_putendl_fd(USAGE, 2);
			exit(1);
		}
		av++;
	}
}

void		parsing_option(char **av, int *nb_opt, t_ls *st_ls)
{
	if (!(*av))
		return ;
	while (*(*av) == '-' && *(*av + 1))
	{
		opt_filler(*av, st_ls);
		(*nb_opt)++;
		if (*(av + 1) && ft_strcmp("--", *(av + 1)))
			av++;
		else
		{
			check_overide(0, st_ls);
			return ;
		}
	}
	check_overide(0, st_ls);
}
