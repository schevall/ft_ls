/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:37:03 by schevall          #+#    #+#             */
/*   Updated: 2017/02/11 19:13:25 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_path(t_file *file, char *parent, char *name)
{
	int		i;

	i = ft_strlen(parent);
	ft_strcpy(file->name, name);
	ft_strcpy(file->path, parent);
	if (ft_strcmp(parent, "/"))
	{
		file->path[i] = '/';
		ft_strcpy(file->path + i + 1, file->name);
	}
	else
		ft_strcpy(file->path + 1, file->name);
}

void	reset_st_ls(t_ls *st_ls)
{
	st_ls->len.link = 0;
	st_ls->len.uid = 0;
	st_ls->len.gid = 0;
	st_ls->len.minor = 0;
	st_ls->len.major = 0;
	st_ls->len.size = 0;
	st_ls->nb_block = 0;
	st_ls->nb_to_print = 0;
}

int		dot(char *path)
{
	int		len;

	len = ft_strlen(path);
	path += len;
	if (*path == '.')
		return (1);
	while (!ft_isalpha(*path))
		path--;
	while (ft_isalpha(*path))
		path--;
	if (*path == '.' && *(path - 1) == '/')
		return (1);
	else
		return (0);
}

int		is_point_rep(char *name)
{
	if (!ft_strcmp(name, "."))
		return (1);
	if (!ft_strcmp(name, ".."))
		return (1);
	return (0);
}
