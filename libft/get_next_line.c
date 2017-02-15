/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 16:38:21 by schevall          #+#    #+#             */
/*   Updated: 2016/12/12 16:41:27 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

static int			link_maker(t_gnl **gnl, int fd)
{
	if (!(*gnl = (t_gnl*)ft_memalloc(sizeof(t_gnl))))
		return (-1);
	(*gnl)->fd = fd;
	(*gnl)->stk = (char*)ft_memalloc(sizeof(char) * 2);
	(*gnl)->end = 0;
	return (1);
}

static int			list_manager(t_gnl **gnl, int fd)
{
	t_gnl			*new;

	new = NULL;
	if (*gnl == NULL)
	{
		if (link_maker(gnl, fd) < 0)
			return (-1);
	}
	else if ((*gnl)->fd != fd)
	{
		while ((*gnl)->prev != NULL)
			*gnl = (*gnl)->prev;
		while ((*gnl)->next != NULL && (*gnl)->fd != fd)
			*gnl = (*gnl)->next;
		if (fd == (*gnl)->fd)
			return (1);
		if (link_maker(&new, fd) < 0)
			return (-1);
		new->prev = *gnl;
		(*gnl)->next = new;
		*gnl = new;
	}
	return (1);
}

static int			throwback_line(t_gnl **gnl, char **line)
{
	int				i;
	char			*tmp;

	i = 0;
	if ((ft_strchr((*gnl)->stk, '\n')))
	{
		while ((*gnl)->stk[i] != '\n')
			i++;
		tmp = (*gnl)->stk;
		*line = ft_strsub((*gnl)->stk, 0, i);
		(*gnl)->stk = ft_strsub((*gnl)->stk, i + 1, ft_strlen((*gnl)->stk));
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

static int			reader(t_gnl **gnl, int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		tmp = (*gnl)->stk;
		if (!((*gnl)->stk = ft_strjoin((*gnl)->stk, buf)))
			return (-1);
		ft_strdel(&tmp);
		if (throwback_line(gnl, line))
			return (1);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl	*gnl = NULL;
	char			*tmp;
	int				ret;

	if (fd < 0 || !line || BUFF_SIZE < 0)
		return (-1);
	if (list_manager(&gnl, fd) < 0)
		return (-1);
	if (throwback_line(&gnl, line))
		return (1);
	if ((ret = reader(&gnl, fd, line)))
		return (ret == 1 ? 1 : -1);
	if (!ft_strchr(gnl->stk, '\n') && ft_strlen(gnl->stk) != 0 && gnl->end == 0)
	{
		gnl->end = 1;
		tmp = gnl->stk;
		if (!(*line = ft_strsub(gnl->stk, 0, ft_strlen(gnl->stk))))
			return (-1);
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}
