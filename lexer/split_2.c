/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:36:43 by lissam            #+#    #+#             */
/*   Updated: 2024/05/22 14:57:36 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_pipe(int *i, char *prompt, t_prompt_nodes **prompt_nodes)
{
	char	*temp;
	char	*str;

	str = NULL;
	while (prompt[*i] == '|')
	{
		temp = (char *)malloc(2 * sizeof(char));
		temp[0] = prompt[*i];
		temp[1] = '\0';
		str = ft_strjoin2(str, temp);
		free(temp);
		*i = *i + 1;
	}
	if (ft_strlen(str) == 1)
		add_to_prompt_nodes(str, &(*prompt_nodes), PIPE);
	else
	{
		free(str);
		return (print_errors_dup("||", *prompt_nodes), 1);
	}
	return (0);
}

void	skip_double_quotes(int *i, char *prompt, char **str)
{
	char	*temp;

	while (prompt[*i] != 34 && prompt[*i] != '\0')
	{
		temp = (char *)malloc(2 * sizeof(char));
		temp[0] = prompt[*i];
		temp[1] = '\0';
		*str = ft_strjoin2(*str, temp);
		free(temp);
		*i = *i + 1;
	}
}

void	skip_single_quote(int *i, char *prompt, char **str)
{
	char	*temp;

	while (prompt[*i] != 39 && prompt[*i] != '\0')
	{
		temp = (char *)malloc(2 * sizeof(char));
		temp[0] = prompt[*i];
		temp[1] = '\0';
		*str = ft_strjoin2(*str, temp);
		free(temp);
		*i = *i + 1;
	}
}

int	split_double_quotes(int *i, char *prompt, t_prompt_nodes **prompt_nodes)
{
	t_prompt_nodes	*tmp_node;
	char			*temp;
	char			*str;

	str = NULL;
	temp = (char *)malloc(2 * sizeof(char));
	temp[0] = prompt[*i];
	temp[1] = '\0';
	str = ft_strjoin2(str, temp);
	free(temp);
	*i = *i + 1;
	skip_double_quotes(i, prompt, &str);
	if (prompt[*i] == '\0')
		return (free(str), 1);
	temp = (char *)malloc(2 * sizeof(char));
	temp[0] = prompt[*i];
	temp[1] = '\0';
	str = ft_strjoin2(str, temp);
	free(temp);
	*i = *i + 1;
	tmp_node = lst_new2(str, STRING);
	ft_lstadd_back2(&(*prompt_nodes), tmp_node);
	return (0);
}

int	split_single_quote(int *i, char *prompt, t_prompt_nodes **prompt_nodes)
{
	t_prompt_nodes	*tmp_node;
	char			*temp;
	char			*str;

	str = NULL;
	temp = (char *)malloc(2 * sizeof(char));
	temp[0] = prompt[*i];
	temp[1] = '\0';
	str = ft_strjoin2(str, temp);
	free(temp);
	*i = *i + 1;
	skip_single_quote(i, prompt, &str);
	if (prompt[*i] == '\0')
		return (free(str), 1);
	temp = (char *)malloc(2 * sizeof(char));
	temp[0] = prompt[*i];
	temp[1] = '\0';
	str = ft_strjoin2(str, temp);
	free(temp);
	*i = *i + 1;
	tmp_node = lst_new2(str, STRING);
	ft_lstadd_back2(&(*prompt_nodes), tmp_node);
	return (0);
}
