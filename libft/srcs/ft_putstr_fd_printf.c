/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:11:44 by eviala            #+#    #+#             */
/*   Updated: 2024/07/24 11:31:25 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd_printf(char *str, int fd)
{
	int	count;

	if (!str)
	{
		count = ft_putstr_fd_printf("(null)", fd);
		return (count);
	}
	count = 0;
	while (str[count])
		count += ft_putchar_fd_printf(str[count], fd);
	return (count);
}
