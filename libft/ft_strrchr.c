/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:14:50 by moel-gha          #+#    #+#             */
/*   Updated: 2023/11/26 16:20:53 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	lenght;

	lenght = ft_strlen(str);
	while (lenght >= 0)
	{
		if (str[lenght] == (char)c)
		{
			return ((char *)&str[lenght]);
		}
		lenght--;
	}
	return (0);
}
