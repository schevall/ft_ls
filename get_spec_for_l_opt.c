/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_spec_for_l_opt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:42:03 by schevall          #+#    #+#             */
/*   Updated: 2017/02/11 18:59:41 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		get_file_type(mode_t st_mode)
{
	if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else
		return ('-');
}

static void	get_bit_specs(char *perm, mode_t st_mode)
{
	if (perm[3] == 'x' && (st_mode & S_ISUID))
		perm[3] = 's';
	if (perm[3] == '-' && (st_mode & S_ISUID))
		perm[3] = 'S';
	if (perm[6] == 'x' && (st_mode & S_ISGID))
		perm[6] = 's';
	if (perm[6] == '-' && (st_mode & S_ISGID))
		perm[6] = 'S';
	if (perm[9] == 'x' && (st_mode & S_ISVTX))
		perm[9] = 't';
	if (perm[9] == '-' && (st_mode & S_ISVTX))
		perm[9] = 'T';
}

void		print_perm(mode_t st_mode, char *perm)
{
	perm[0] = get_file_type(st_mode);
	perm[1] = (st_mode & S_IRUSR ? 'r' : '-');
	perm[2] = (st_mode & S_IWUSR ? 'w' : '-');
	perm[3] = (st_mode & S_IXUSR ? 'x' : '-');
	perm[4] = (st_mode & S_IRGRP ? 'r' : '-');
	perm[5] = (st_mode & S_IWGRP ? 'w' : '-');
	perm[6] = (st_mode & S_IXGRP ? 'x' : '-');
	perm[7] = (st_mode & S_IROTH ? 'r' : '-');
	perm[8] = (st_mode & S_IWOTH ? 'w' : '-');
	perm[9] = (st_mode & S_IXOTH ? 'x' : '-');
	get_bit_specs(perm, st_mode);
	perm[10] = '\0';
	ft_printf("%s", perm);
}

static char	*get_time_extended(char *output, char *str_time, time_t time_ref)
{
	time_t	now;
	char	*tmp;

	time(&now);
	output = ft_strnew(13);
	output = ft_strncpy(output, str_time + 4, 6);
	output[6] = ' ';
	output[7] = ' ';
	if (now - time_ref < -251751888000)
		output = ft_strjoin(output, "10000");
	else
	{
		tmp = output;
		output = ft_strjoin(output, str_time + 20);
		free(tmp);
		output[12] = '\0';
	}
	return (output);
}

char		*get_time(time_t time_ref)
{
	time_t	now;
	char	*str_time;
	char	*output;

	output = NULL;
	time(&now);
	str_time = ctime(&time_ref);
	if (now - time_ref > 15778476 || now - time_ref < -3600)
		output = get_time_extended(output, str_time, time_ref);
	else
		output = ft_strsub(str_time, 4, 12);
	return (output);
}
