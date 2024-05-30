/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:12:27 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/21 12:23:22 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_overflow(long rslt, int sign, char next)
{
	if (rslt > (LONG_MAX - (next - '0')) / 10)
	{
		if (sign == 1)
			return (1);
		else
			return (-1);
	}
	return (0);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		overflow_check;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (LONG_MAX);
		overflow_check = check_overflow(result, sign, *str);
		if (overflow_check == 1)
			return (LONG_MAX);
		else if (overflow_check == -1)
			return (LONG_MIN);
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
