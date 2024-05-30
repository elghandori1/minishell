/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_list_env2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:16:31 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/23 21:21:58 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**allocate_key_value(const char *str, const char *equal_pos)
{
	char	**result;
	int		key_len;

	key_len = equal_pos - str;
	result = (char **)malloc(3 * sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = (char *)malloc((key_len + 1) * sizeof(char));
	if (!result[0])
	{
		free(result);
		return (NULL);
	}
	ft_strlcpy(result[0], str, key_len + 1);
	result[1] = strdup(equal_pos + 1);
	result[2] = NULL;
	return (result);
}

char	**split_first_equal(char *str)
{
	char	**result;
	char	*equal_pos;

	equal_pos = ft_strchr(str, '=');
	if (equal_pos == NULL)
	{
		result = (char **)malloc(3 * sizeof(char *));
		if (!result)
			return (NULL);
		result[0] = ft_strdup(str);
		result[1] = NULL;
		result[2] = NULL;
		return (result);
	}
	return (allocate_key_value(str, equal_pos));
}

void	free_split_result(char **split_result)
{
	int	i;

	i = 0;
	while (split_result[i])
	{
		free(split_result[i]);
		i++;
	}
	free(split_result);
}
