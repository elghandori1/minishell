/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:35:32 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/22 10:38:04 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_g_lobal_env(void)
{
	t_env	*current;
	t_env	*next;

	current = g_lobal_env;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	g_lobal_env = NULL;
}

void	success(void)
{
	printf("exit\n");
	exit(g_lobal_env->status);
	cleanup_g_lobal_env();
}

int	count_arguments(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}

void	ft_exit(t_cmd *head)
{
	char	**args;
	long	exit_code;

	args = &head->args[1];
	if (count_arguments(args) > 1)
	{
		(printf("exit: too many arguments\n"), set_status(1));
		return ;
	}
	else if (*args)
	{
		exit_code = ft_atol(*args);
		if (exit_code == LONG_MAX || exit_code == LONG_MIN)
		{
			printf("exit\n%s: numeric argument required\n", *args);
			(cleanup_g_lobal_env(), exit(255));
		}
		else
		{
			(printf("exit\n"), cleanup_g_lobal_env());
			exit((int)exit_code % 256);
		}
	}
	else
		success();
}
