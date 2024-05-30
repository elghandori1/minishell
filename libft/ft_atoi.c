/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:12:18 by moel-gha          #+#    #+#             */
/*   Updated: 2023/11/27 09:11:36 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_long(size_t rt, int sn)
{
	if ((rt >= 9223372036854775807) && (sn > 0))
		return (-1);
	if ((rt > 9223372036854775807) && (sn < 0))
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	rslt;

	sign = 1;
	rslt = 0;
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		rslt = (rslt * 10 + *str) - '0';
		if (ft_check_long(rslt, sign) != 1)
			return (ft_check_long(rslt, sign));
		str++;
	}
	return (rslt * sign);
}
