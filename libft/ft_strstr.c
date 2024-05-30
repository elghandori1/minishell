/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:44:59 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/23 19:46:34 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	compare_substring(char *haystack, char *needle)
{
	while (*needle != '\0' && *haystack == *needle)
	{
		haystack++;
		needle++;
	}
	return (*needle == '\0');
}

char	*ft_strstr(char *haystack, char *needle)
{
	char	*p;
	char	*begin;

	if (*needle == '\0')
		return (haystack);
	p = haystack;
	while (*p != '\0')
	{
		if (*p == *needle)
		{
			begin = p;
			if (compare_substring(begin, needle))
				return (begin);
			p = begin + 1;
		}
		else
			p++;
	}
	return (NULL);
}
