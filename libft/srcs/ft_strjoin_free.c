/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:51:46 by eviala            #+#    #+#             */
/*   Updated: 2024/06/21 15:24:10 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	i;
	size_t	len;
	char	*s3;

	len = (ft_strlen(s1) + ft_strlen(s2));
	i = 0;
	s3 = (char *)ft_calloc(len + 1, sizeof(char));
	if (!s3)
		return (NULL);
	while (i < len)
	{
		while (*s1)
			s3[i++] = *s1++;
		while (*s2)
			s3[i++] = *s2++;
	}
	s3[i] = '\0';
	free(s1);
	return (s3);
}
