/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:38:01 by moel-gha          #+#    #+#             */
/*   Updated: 2023/11/24 17:54:24 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int c)
{
	int	count;

	count = 0;
	if (c < 0)
		count += 1;
	while (c != 0)
	{
		count++;
		c /= 10;
	}
	count += 1;
	return (count);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = count_digit(n);
	str = malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	str[len - 1] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	i = len - 2;
	while (n != 0)
	{
		str[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
