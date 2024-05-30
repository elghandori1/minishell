/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_list_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:48:30 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/25 20:44:05 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit(EXIT_FAILURE);
	node->key = ft_strdup(key);
	if (value != NULL)
	{
		node->value = ft_strdup(value);
	}
	else
	{
		node->value = NULL;
	}
	node->status = 0;
	node->next = NULL;
	return (node);
}

void	ft_add_env_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		last = *lst;
		while (last->next)
		{
			last = last->next;
		}
		last->next = new;
	}
}

void	update_env_value(t_env *my_env, char *key, char *value)
{
	t_env	*temp;
	t_env	*new_node;

	temp = my_env;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
	new_node = new_env_node(key, value);
	ft_add_env_back(&my_env, new_node);
}

t_env	*behavior_env(void)
{
	t_env	*my_env;
	t_env	*new_node;

	my_env = NULL;
	new_node = new_env_node("PWD", "/nfs/homes/moel-gha/Desktop/minishell");
	ft_add_env_back(&my_env, new_node);
	new_node = new_env_node("SHLVL", "1");
	ft_add_env_back(&my_env, new_node);
	new_node = new_env_node("OLDPWD", "");
	ft_add_env_back(&my_env, new_node);
	new_node = new_env_node("_", "/usr/bin/env");
	ft_add_env_back(&my_env, new_node);
	return (my_env);
}

t_env	*convert_env(char **en)
{
	t_env	*my_env;
	t_env	*new_node;
	char	**path;
	int		i;

	my_env = NULL;
	new_node = NULL;
	i = 0;
	while (en[i] != NULL)
	{
		path = split_first_equal(en[i]);
		if (path)
		{
			new_node = new_env_node(path[0], path[1]);
			ft_add_env_back(&my_env, new_node);
			free_split_result(path);
		}
		i++;
	}
	return (my_env);
}
