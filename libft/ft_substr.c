/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 09:39:29 by moel-gha          #+#    #+#             */
/*   Updated: 2023/11/11 10:58:51 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	taille;
	char	*str;

	if (!s)
		return (NULL);
	taille = ft_strlen(s);
	if ((*s == '\0') || (start >= taille))
		return (ft_calloc(1, 1));
	else if (len > (taille - start))
		len = taille - start;
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
