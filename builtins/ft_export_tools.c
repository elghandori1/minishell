/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:48:13 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/26 11:07:37 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_env(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	bubble_sort_env(t_env *head)
{
	int		swapped;
	t_env	*lptr;
	t_env	*ptr1;

	swapped = 1;
	lptr = NULL;
	ptr1 = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap_env(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		if (!swapped)
			break ;
		lptr = ptr1;
	}
}

int	check_parexport(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str != '=' && *str != '\0')
	{
		if (*str == '+' && *(str + 1) == '=')
			return (1);
		if (!ft_isalpha(*str) && !ft_isalnum(*str))
			return (0);
		str++;
	}
	return (1);
}

void	show_export(t_env *head)
{
	t_env	*envg;

	envg = head;
	while (envg)
	{
		if ((ft_strcmp(envg->key, "OLDPWD") == 0) && (*envg->value == '\0'))
			printf("declare -x %s\n", envg->key);
		else if (envg->value != NULL && *envg->value != '\0'
			&& (ft_strcmp(envg->key, "_") != 0))
			printf("declare -x %s=\"%s\"\n", envg->key, envg->value);
		else if (envg->value != NULL && *envg->value == '\0')
			printf("declare -x %s=\"\"\n", envg->key);
		else if (envg->value == NULL)
			printf("declare -x %s\n", envg->key);
		envg = envg->next;
	}
}

void	append_value_env(t_env **g_env, char *variable, char *valueapp)
{
	t_env	*exist_node;
	char	*new_value;
	size_t	total_len;

	exist_node = *g_env;
	while (exist_node != NULL)
	{
		if (ft_strcmp(exist_node->key, variable) == 0)
		{
			total_len = ft_strlen(exist_node->value) + ft_strlen(valueapp);
			new_value = (char *)malloc(ft_strlen(exist_node->value)
					+ ft_strlen(valueapp) + 1);
			if (new_value != NULL)
			{
				ft_strcpy(new_value, exist_node->value);
				ft_strlcat(new_value, valueapp, total_len + 1);
				free(exist_node->value);
				exist_node->value = new_value;
			}
			break ;
		}
		exist_node = exist_node->next;
	}
}
