/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_toarray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:49:20 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/25 16:27:30 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_list_size(t_env *env)
{
	int		size;
	t_env	*tmp;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**env_to_array(t_env *env)
{
	t_env	*tmp;
	char	**env_array;

	if (!env)
		return (NULL);
	int (size), (length), (i);
	size = env_list_size(env);
	env_array = malloc((size + 1) * sizeof(char *));
	if (!env_array)
		exit(1);
	tmp = env;
	i = 0;
	while (tmp)
	{
		length = ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2;
		env_array[i] = malloc(length * sizeof(char));
		if (!env_array[i])
			exit(0);
		ft_strcpy(env_array[i], tmp->key);
		(ft_strcat(env_array[i], "="), ft_strcat(env_array[i], tmp->value));
		tmp = tmp->next;
		i++;
	}
	env_array[size] = NULL;
	return (env_array);
}
