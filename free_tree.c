/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:37:05 by schevall          #+#    #+#             */
/*   Updated: 2017/02/10 17:09:41 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		free_tree(t_node **tree)
{
	if (*tree)
	{
		if ((*tree)->left)
			free_tree(&(*tree)->left);
		if ((*tree)->right)
			free_tree(&(*tree)->right);
		if ((*tree)->name)
			free((*tree)->name);
		if ((*tree)->path)
			free((*tree)->path);
		if ((*tree)->name_uid)
			free((*tree)->name_uid);
		if ((*tree)->name_gid)
			free((*tree)->name_gid);
		free(*tree);
		*tree = NULL;
	}
}

void		free_st_ls(t_ls **st_ls)
{
	if (*st_ls)
	{
		free((*st_ls)->opt);
	}
}
