/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:25:57 by schevall          #+#    #+#             */
/*   Updated: 2017/02/10 18:53:03 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	padding_info(t_ls *st_ls, t_node *elem)
{
	int				i;

	if (st_ls->len.link < (i = ft_nbrlen(elem->nlink)))
		st_ls->len.link = i;
	if (st_ls->len.size < (i = ft_nbrlen(elem->size)))
		st_ls->len.size = i;
	if (st_ls->len.minor < (i = ft_nbrlen(elem->minor)))
		st_ls->len.minor = i;
	if (st_ls->len.major < (i = ft_nbrlen(elem->major)))
		st_ls->len.major = i;
	if (st_ls->len.uid < (i = ft_strlen(elem->name_uid)))
		st_ls->len.uid = i;
	if (st_ls->len.gid < (i = ft_strlen(elem->name_gid)))
		st_ls->len.gid = i;
}

void			get_padding_info(t_node *tree, t_ls *st_ls)
{
	if (!tree)
		return ;
	if (tree->left)
		get_padding_info(tree->left, st_ls);
	padding_info(st_ls, tree);
	if (tree->right)
		get_padding_info(tree->right, st_ls);
}

static	void	get_names(t_node *tree, t_ls *st_ls)
{
	struct passwd	*uid;
	struct group	*gid;

	if (!(uid = getpwuid(tree->uid)))
		tree->name_uid = ft_itoa(tree->uid);
	else
	{
		if (!(tree->name_uid = ft_strdup(uid->pw_name)))
			ls_error(NULL, 0, st_ls);
	}
	if (!(gid = getgrgid(tree->gid)))
		tree->name_gid = ft_itoa(tree->gid);
	else
	{
		if (!(tree->name_gid = ft_strdup(gid->gr_name)))
			ls_error(NULL, 0, st_ls);
	}
}

static	void	get_time_option(t_ls *st_ls, t_node *elem, t_stat buf)
{
	if (st_ls->opt['c'])
		elem->time_ref = buf.st_ctime;
	else if (st_ls->opt['u'])
		elem->time_ref = buf.st_atime;
	else if (st_ls->opt['U'])
		elem->time_ref = buf.st_birthtime;
	else
		elem->time_ref = buf.st_mtime;
}

t_node			*creat_elem(t_stat buf, t_ls *st_ls, t_file file)
{
	t_node			*elem;

	if (!(elem = (t_node*)ft_memalloc(sizeof(t_node))))
		ls_error(NULL, 0, st_ls);
	if (!(elem->name = ft_strdup(file.name)))
		ls_error(NULL, 0, st_ls);
	if (!(elem->path = ft_strdup(file.path)))
		ls_error(NULL, 0, st_ls);
	elem->mode = buf.st_mode;
	elem->nlink = buf.st_nlink;
	elem->uid = buf.st_uid;
	elem->gid = buf.st_gid;
	get_names(elem, st_ls);
	elem->rdev = buf.st_rdev;
	elem->size = buf.st_size;
	elem->minor = minor(elem->rdev);
	elem->major = major(elem->rdev);
	elem->blocks = buf.st_blocks;
	get_time_option(st_ls, elem, buf);
	return (elem);
}
