/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:36:40 by schevall          #+#    #+#             */
/*   Updated: 2017/02/10 18:53:05 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	add_node_default(t_node *elem, t_node **tree, t_ls *st_ls)
{
	t_node *tmp;

	tmp = *tree;
	if (ft_strcmp(elem->name, (*tree)->name) > 0 || st_ls->opt['f'])
	{
		*tree = (*tree)->right;
		if (!(*tree))
			tmp->right = elem;
	}
	else
	{
		*tree = (*tree)->left;
		if (!(*tree))
			tmp->left = elem;
	}
}

static void	add_node_t(t_node *elem, t_node *tree, t_ls *st_ls)
{
	t_node *tmp;

	while (tree)
	{
		tmp = tree;
		if (elem->time_ref == tree->time_ref)
			add_node_default(elem, &tree, st_ls);
		else if (elem->time_ref < tree->time_ref || st_ls->opt['f'])
		{
			tree = tree->right;
			if (!tree)
				tmp->right = elem;
		}
		else
		{
			tree = tree->left;
			if (!tree)
				tmp->left = elem;
		}
	}
}

static void	add_node_s(t_node *elem, t_node *tree, t_ls *st_ls)
{
	t_node *tmp;

	while (tree)
	{
		tmp = tree;
		if (elem->size == tree->size)
			add_node_default(elem, &tree, st_ls);
		else if (elem->size < tree->size || st_ls->opt['f'])
		{
			tree = tree->right;
			if (!tree)
				tmp->right = elem;
		}
		else
		{
			tree = tree->left;
			if (!tree)
				tmp->left = elem;
		}
	}
}

void		add_node(t_node **tree, t_stat buf, t_ls *st_ls, t_file file)
{
	t_node *elem;
	t_node *tmp;

	elem = creat_elem(buf, st_ls, file);
	if (*tree)
	{
		tmp = *tree;
		if (st_ls->opt['t'])
			add_node_t(elem, *tree, st_ls);
		else if (st_ls->opt['S'])
			add_node_s(elem, *tree, st_ls);
		else
		{
			while (tmp)
				add_node_default(elem, &tmp, st_ls);
		}
	}
	else
		*tree = elem;
}
