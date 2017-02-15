/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 16:45:12 by schevall          #+#    #+#             */
/*   Updated: 2017/01/10 10:32:48 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 32
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include "./libft.h"

typedef struct		s_gnl
{
	int				fd;
	char			*stk;
	int				end;
	struct s_gnl	*next;
	struct s_gnl	*prev;
}					t_gnl;

int					get_next_line(const int fd, char **line);

#endif
