/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:15:16 by moel-gha          #+#    #+#             */
/*   Updated: 2023/11/07 11:46:17 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	ut_c;
	size_t			i;

	s = (unsigned char *)str;
	ut_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s[i] == ut_c)
		{
			return ((void *)(s + i));
		}
		i++;
	}
	return (0);
}
