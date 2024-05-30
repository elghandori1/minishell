/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:48:15 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/22 10:38:32 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_or_update_env(t_env **g_lobal_env, char *key, char *value)
{
	t_env	*current_node;
	t_env	*new_node;

	current_node = *g_lobal_env;
	while (current_node != NULL)
	{
		if (ft_strcmp(current_node->key, key) == 0)
		{
			free(current_node->value);
			if (value != NULL && *value != '\0')
				current_node->value = ft_strdup(value);
			else if (value != NULL && *value == '\0')
				current_node->value = ft_strdup("");
			else
				current_node->value = NULL;
			return ;
		}
		current_node = current_node->next;
	}
	new_node = new_env_node(key, value);
	ft_add_env_back(g_lobal_env, new_node);
}

void	handle_append(char *string, t_env **g_env)
{
	char	*pls_eql;
	char	*value_to_append;
	t_env	*current_node;
	char	*old_value;
	char	*new_value;

	pls_eql = ft_strstr(string, "+=");
	if (pls_eql == NULL)
		return ;
	*pls_eql = '\0';
	value_to_append = pls_eql + 2;
	current_node = *g_env;
	while (current_node != NULL)
	{
		if (ft_strcmp(current_node->key, string) == 0)
		{
			old_value = current_node->value;
			new_value = ft_strjoin(old_value, value_to_append);
			free(current_node->value);
			current_node->value = new_value;
			return ;
		}
		current_node = current_node->next;
	}
	add_or_update_env(g_env, string, value_to_append);
}

void	regular_export(char *string, t_env **g_lobal_env)
{
	char	*equal_sign_position;
	char	*key;
	char	*value;

	equal_sign_position = ft_strchr(string, '=');
	if (equal_sign_position != NULL)
	{
		*equal_sign_position = '\0';
		key = string;
		value = equal_sign_position + 1;
		add_or_update_env(g_lobal_env, key, value);
	}
	else
		add_or_update_env(g_lobal_env, string, NULL);
}

void	export_or_append(char *string, t_env **g_lobal_env)
{
	if (ft_strstr(string, "+=") != NULL)
	{
		handle_append(string, g_lobal_env);
	}
	else
	{
		regular_export(string, g_lobal_env);
	}
}

void	ft_export(t_cmd *hd)
{
	char	*string;
	int		i;

	i = 0;
	if (hd->args[1] != NULL)
	{
		while (hd->args[++i] != NULL)
		{
			if (check_parexport(hd->args[i]))
			{
				string = hd->args[i];
				if (ft_strchr(string, '=') != NULL)
					export_or_append(string, &g_lobal_env);
				else
				{
					if (!isexistenv(g_lobal_env, string))
						add_or_update_env(&g_lobal_env, string, NULL);
				}
			}
			else
				printf("export:`%s` :not a valid identifier\n", hd->args[i]);
		}
	}
	else
		(bubble_sort_env(g_lobal_env), show_export(g_lobal_env));
}
