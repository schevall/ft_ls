/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_acl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:03:02 by schevall          #+#    #+#             */
/*   Updated: 2017/02/10 15:04:12 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_acl(t_node *tree)
{
	char	*tmp;
	acl_t	tmp2;
	char	tmp3[101];

	if (*(tree->path + 1) == '/' && *tree->path == '/')
		tmp = ft_strdup(tree->path + 1);
	else
		tmp = ft_strdup(tree->path);
	if (listxattr(tmp, tmp3, sizeof(tmp3), XATTR_NOFOLLOW) > 0)
		ft_printf("@");
	else if ((tmp2 = acl_get_file(tmp, ACL_TYPE_EXTENDED)))
	{
		acl_free(tmp2);
		ft_printf("+");
	}
	else
		ft_printf(" ");
}
