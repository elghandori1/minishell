/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:48:21 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/26 20:39:35 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_env_var(char *arg)
{
	t_env	*temp;
	t_env	*prev;

	temp = g_lobal_env;
	prev = NULL;
	while (temp != NULL && ft_strcmp(temp->key, arg) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp != NULL)
	{
		if (prev == NULL)
			g_lobal_env = temp->next;
		else
			prev->next = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	ft_unset(t_cmd *head)
{
	char	**args;

	args = head->args;
	while (*args != NULL)
	{
		if (ft_strcmp(*args, "_") != 0)
		{
			remove_env_var(*args);
		}
		args++;
	}
}
