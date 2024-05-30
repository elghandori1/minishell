/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:48:00 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/25 20:43:23 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_nodes(t_env *my_env)
{
	t_env	*temp;
	t_env	*lastnode;

	lastnode = NULL;
	temp = my_env;
	while (temp != NULL)
	{
		if (temp->value != NULL && temp->value[0] != '\0')
		{
			if (ft_strcmp(temp->key, "_") == 0)
				lastnode = temp;
			else
				printf("%s=%s\n", temp->key, temp->value);
		}
		temp = temp->next;
	}
	if (lastnode != NULL)
		printf("%s=%s\n", lastnode->key, lastnode->value);
}

int	isexistenv(t_env *env, char *key)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_env(t_env *my_env)
{
	display_nodes(my_env);
}
