/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:47:57 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/21 12:47:58 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_echo(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	set_status(0);
}

void	ft_echo(t_cmd *all)
{
	char	**args;
	char	*opt;
	int		print_newline;

	print_newline = 1;
	args = all->args;
	args++;
	while (*args && (*args)[0] == '-')
	{
		opt = *args;
		opt++;
		while (*opt == 'n')
			opt++;
		if (*opt == '\0')
		{
			print_newline = 0;
			args++;
		}
		else
			break ;
	}
	show_echo(args);
	if (print_newline)
		printf("\n");
}
