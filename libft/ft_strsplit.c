/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:54:16 by schevall          #+#    #+#             */
/*   Updated: 2016/11/21 18:12:16 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	line_index;
	size_t	word_len;

	if (!s)
		return (NULL);
	i = 0;
	line_index = ft_count_word(s, c);
	if (!(res = ft_memalloc(sizeof(char*) * (line_index + 1))))
		return (NULL);
	line_index = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word_len = ft_word_len(s, i, c);
			res[line_index] = ft_strsub(s, i, word_len);
			i = i + word_len;
			line_index++;
		}
		else
			i++;
	}
	return (res);
}
