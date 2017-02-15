/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:00:06 by schevall          #+#    #+#             */
/*   Updated: 2017/02/11 19:16:32 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		init_file(char *arg, t_file *file)
{
	int i;

	i = 0;
	ft_bzero(file, sizeof(t_file));
	while (i < NAME_MAX + 1 && arg[i])
	{
		file->path[i] = arg[i];
		file->name[i] = arg[i];
		i++;
	}
	file->path[i] = '\0';
	file->name[i] = '\0';
	return (1);
}

void	add_arg_to_list(t_node **tree, char *arg, t_ls *st_ls)
{
	t_file file;
	t_stat buf;

	if (init_file(arg, &file))
	{
		if (st_ls->opt['l'])
		{
			if (lstat(arg, &buf) != -1)
				add_node(tree, buf, st_ls, file);
			else
				ls_error(arg, 1, st_ls);
		}
		else
		{
			if (stat(arg, &buf) != -1)
				add_node(tree, buf, st_ls, file);
			else if (lstat(arg, &buf) != -1)
				add_node(tree, buf, st_ls, file);
			else
				ls_error(arg, 1, st_ls);
		}
	}
}

void	list_arg(t_node **tree, char **av, t_ls *st_ls)
{
	int i;

	i = 0;
	if (!(*av))
		add_arg_to_list(tree, ".", st_ls);
	while (av[i])
	{
		add_arg_to_list(tree, av[i], st_ls);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_ls	*st_ls;
	t_node	*tree;
	int		nb_opt;

	nb_opt = 0;
	if (!(st_ls = ft_memalloc(sizeof(t_ls))))
		ls_error(NULL, 0, st_ls);
	av++;
	parsing_option(av, &nb_opt, st_ls);
	av += nb_opt;
	if (*av && *(*av) == '-' && *(*av + 1) == '-')
	{
		av++;
		ac--;
	}
	ac -= (nb_opt + 1);
	if ((!st_ls->opt['f']))
		av = ft_sort_params(ac, av);
	list_arg(&tree, av, st_ls);
	print_tree(tree, st_ls, 1);
	if (!st_ls->opt['d'])
		print_dir(tree, st_ls, ac, 1);
	free_tree(&tree);
	free_st_ls(&st_ls);
	return (0);
}
