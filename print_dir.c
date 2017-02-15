/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 16:42:45 by schevall          #+#    #+#             */
/*   Updated: 2017/02/11 19:33:29 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_dir_files(char *parent, t_ls *st_ls, t_node **elem, char *name)
{
	DIR		*dirp;
	t_dir	*dir;
	t_stat	buf;
	t_file	file;

	reset_st_ls(st_ls);
	if (!(dirp = opendir(parent)))
		return (ls_error(name, 1, st_ls));
	while ((dir = readdir(dirp)) != NULL)
	{
		get_path(&file, parent, dir->d_name);
		if (!(*file.name == '.') || ((*file.name == '.') && st_ls->opt['a']))
		{
			if (lstat(file.path, &buf) == -1)
				ls_error(file.name, 1, st_ls);
			else
			{
				add_node(elem, buf, st_ls, file);
				st_ls->nb_block += buf.st_blocks;
				st_ls->nb_to_print++;
			}
		}
	}
	closedir(dirp);
}

void	print_dir_files(t_node *tree, t_ls *st_ls, int size)
{
	t_node	*elem;

	elem = NULL;
	st_ls->nb_to_print = 0;
	if (size != 1 && st_ls->printed && (!dot(tree->name) || st_ls->opt['a']))
	{
		st_ls->printed = 0;
		ft_printf("\n");
	}
	if (size > 1 && ((st_ls->opt['a'] && dot(tree->path)) || !dot(tree->path)))
	{
		st_ls->printed = 1;
		ft_printf("%s:", tree->path);
		ft_printf("\n");
	}
	if (!dot(tree->path) || st_ls->opt['a'])
		get_dir_files(tree->path, st_ls, &elem, tree->name);
	if (st_ls->opt['l'] && st_ls->nb_to_print > 0)
		ft_printf("total %d\n", st_ls->nb_block);
	print_tree(elem, st_ls, 2);
	print_dir(elem, st_ls, 2, 2);
	free_tree(&elem);
}

void	print_def_d(t_node *tree, t_ls *st_ls, int size, int mode)
{
	if (!tree || (mode == 2 && !st_ls->opt['R']))
		return ;
	if (tree->left)
		print_def_d(tree->left, st_ls, size, mode);
	if (S_ISDIR(tree->mode) && (!is_point_rep(tree->name) || mode == 1))
		print_dir_files(tree, st_ls, size);
	if (tree->right)
		print_def_d(tree->right, st_ls, size, mode);
}

void	print_rev_d(t_node *tree, t_ls *st_ls, int size, int mode)
{
	if (!tree || (mode == 2 && !st_ls->opt['R']))
		return ;
	if (tree->right)
		print_rev_d(tree->right, st_ls, size, mode);
	if (S_ISDIR(tree->mode) && (!is_point_rep(tree->name) || mode == 1))
		print_dir_files(tree, st_ls, size);
	if (tree->left)
		print_rev_d(tree->left, st_ls, size, mode);
}

void	print_dir(t_node *tree, t_ls *st_ls, int size, int mode)
{
	if (!tree)
		return ;
	if (dot(tree->path) && !st_ls->opt['a'])
		return ;
	if (st_ls->opt['r'])
		print_rev_d(tree, st_ls, size, mode);
	else
		print_def_d(tree, st_ls, size, mode);
}
