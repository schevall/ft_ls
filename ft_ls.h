/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:43:50 by schevall          #+#    #+#             */
/*   Updated: 2017/02/10 16:59:03 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <dirent.h>
# include <time.h>
# include <errno.h>
# include <limits.h>
# include <sys/xattr.h>
# include <sys/acl.h>

# include "./libft/libft.h"

# define OPTION_LIST "acfdlprRStuU1";
# define ILLEGAL "ls: illegal option -- "
# define USAGE "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]"

typedef struct dirent	t_dir;
typedef struct stat		t_stat;

typedef struct			s_file
{
	char	name[NAME_MAX + 1];
	char	path[PATH_MAX];
}						t_file;

typedef struct			s_len
{
	int	link;
	int uid;
	int	gid;
	int minor;
	int major;
	int	size;
}						t_len;

typedef struct			s_ls
{
	char			opt[128];
	struct s_len	len;
	int				printed;
	int				nb_block;
	int				nb_to_print;
	int				error;
}						t_ls;

typedef struct			s_node
{
	char			*name;
	char			*path;
	mode_t			mode;
	nlink_t			nlink;
	uid_t			uid;
	char			*name_uid;
	gid_t			gid;
	char			*name_gid;
	dev_t			rdev;
	int				minor;
	int				major;
	time_t			time_ref;
	off_t			size;
	blkcnt_t		blocks;
	struct s_node	*left;
	struct s_node	*right;
}						t_node;

void					parsing_option(char **av, int *nb_opt, t_ls *st_ls);
void					print_tree(t_node *tree, t_ls *st_ls, int mode);
void					print_perm(mode_t st_mode, char *perm);
char					*get_time(time_t time_ref);
void					print_acl(t_node *tree);
char					get_file_type(mode_t st_mode);
void					print_dir(t_node *tree, t_ls *st_ls, int size,
																	int mode);
t_node					*creat_elem(t_stat buf, t_ls *st_ls, t_file file);
void					get_padding_info(t_node *tree, t_ls *st_ls);
void					add_node(t_node **tree, t_stat buf, t_ls *st_ls,
																t_file file);
void					ls_error(char *str, int mode, t_ls *st_ls);
int						is_point_rep(char *name);
int						dot(char *path);
void					get_path(t_file *file, char *parent, char *name);
void					reset_st_ls(t_ls *st_ls);
void					free_tree(t_node **tree);
void					free_st_ls(t_ls **st_ls);
#endif
