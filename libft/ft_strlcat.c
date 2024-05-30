/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:28:57 by moel-gha          #+#    #+#             */
/*   Updated: 2023/11/30 15:32:25 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	lent_src;
	size_t	lent_dest;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	lent_dest = ft_strlen(dst);
	lent_src = ft_strlen(src);
	i = lent_dest;
	j = 0;
	if (dstsize == 0 || dstsize <= lent_dest)
	{
		return (lent_src + dstsize);
	}
	while ((j < dstsize - lent_dest - 1) && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (lent_src + lent_dest);
}
