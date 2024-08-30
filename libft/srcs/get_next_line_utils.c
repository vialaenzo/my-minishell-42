/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:26:41 by eviala            #+#    #+#             */
/*   Updated: 2024/07/05 11:34:39 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *stash_c, char *buffer)
{
	size_t	len;
	char	*n_stash_c;

	char *(tmp_line) = stash_c;
	len = (ft_strlen(stash_c) + ft_strlen(buffer));
	size_t (i) = 0;
	n_stash_c = (char *)malloc(len + 1 * sizeof(char));
	if (!n_stash_c)
		return (NULL);
	while (i < len)
	{
		while (*stash_c)
			n_stash_c[i++] = *stash_c++;
		while (*buffer)
			n_stash_c[i++] = *buffer++;
	}
	n_stash_c[i] = '\0';
	free(tmp_line);
	return (n_stash_c);
}
