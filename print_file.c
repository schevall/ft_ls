/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utre.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:21:28 by schevall          #+#    #+#             */
/*   Updated: 2017/02/10 17:46:50 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_l_opt(t_node *tree, t_ls *st_ls)
{
	char	perm[11];

	print_perm(tree->mode, perm);
	print_acl(tree);
	ft_printf(" %*d", st_ls->len.link, tree->nlink);
	ft_printf(" %-*s ", st_ls->len.uid, tree->name_uid);
	ft_printf(" %-*s ", st_ls->len.gid, tree->name_gid);
	if (perm[0] == 'b' || perm[0] == 'c')
		ft_printf(" %*d, %*d ", st_ls->len.major + 1,
			tree->major, st_ls->len.minor + 1, tree->minor);
	else
		ft_printf(" %*d ", st_ls->len.size, tree->size);
	ft_printf("%s ", get_time(tree->time_ref));
}

static void	print_file(t_node *tree, t_ls *st_ls)
{
	char	link[PATH_MAX];

	if (!st_ls->opt['a'] && (is_point_rep(tree->name)
		|| *tree->name == '.') && !st_ls->opt['d'])
		return ;
	if (st_ls->opt['l'])
		print_l_opt(tree, st_ls);
	ft_printf("%s", tree->name);
	if (st_ls->opt['p'] && S_ISDIR(tree->mode))
		ft_printf("/");
	if (S_ISLNK(tree->mode) && st_ls->opt['l'])
	{
		ft_bzero(link, PATH_MAX);
		readlink(tree->path, link, PATH_MAX);
		ft_printf(" -> %s", link);
	}
	ft_printf("\n");
	st_ls->printed = 1;
}

static void	print_tree_def(t_node *tree, t_ls *st_ls, int mode)
{
	if (!tree)
		return ;
	if (tree->left)
		print_tree_def(tree->left, st_ls, mode);
	if ((mode == 1 && !S_ISDIR(tree->mode)) || mode == 2 || st_ls->opt['d'])
		print_file(tree, st_ls);
	if (tree->right)
		print_tree_def(tree->right, st_ls, mode);
}

static void	print_tree_rev(t_node *tree, t_ls *st_ls, int mode)
{
	if (!tree)
		return ;
	if (tree->right)
		print_tree_rev(tree->right, st_ls, mode);
	if ((mode == 1 && !S_ISDIR(tree->mode)) || mode == 2)
		print_file(tree, st_ls);
	if (tree->left)
		print_tree_rev(tree->left, st_ls, mode);
}

void		print_tree(t_node *tree, t_ls *st_ls, int mode)
{
	if (!tree)
		return ;
	if (st_ls->opt['l'])
		get_padding_info(tree, st_ls);
	if (st_ls->opt['r'])
		print_tree_rev(tree, st_ls, mode);
	else
		print_tree_def(tree, st_ls, mode);
}
