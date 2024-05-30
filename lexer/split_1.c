/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:36:37 by lissam            #+#    #+#             */
/*   Updated: 2024/05/26 17:04:38 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_chars(int *i, char *prompt, t_prompt_nodes **prompt_nodes)
{
	char	*temp;
	char	*str;

	str = NULL;
	temp = NULL;
	while (prompt[*i] != '>' && prompt[*i] != '<' && prompt[*i] != '|'
		&& prompt[*i] != 34 && prompt[*i] != 39 && prompt[*i] != ' '
		&& (prompt[*i] > 13 || prompt[*i] < 9) && prompt[*i] != '\0')
	{
		temp = (char *)malloc(2 * sizeof(char));
		temp[0] = prompt[*i];
		temp[1] = '\0';
		str = ft_strjoin2(str, temp);
		free(temp);
		*i = *i + 1;
	}
	add_to_prompt_nodes(str, &(*prompt_nodes), STRING);
}

int	split_output_redirection(int *i, char *prompt,
		t_prompt_nodes **prompt_nodes)
{
	char	*temp;
	char	*str;

	str = NULL;
	while (prompt[*i] == '>')
	{
		temp = (char *)malloc(2 * sizeof(char));
		temp[0] = prompt[*i];
		temp[1] = '\0';
		str = ft_strjoin2(str, temp);
		free(temp);
		*i = *i + 1;
	}
	if (ft_strlen(str) == 1)
		add_to_prompt_nodes(str, &(*prompt_nodes), REDIRECT_OUTPUT);
	else if (ft_strlen(str) == 2)
		add_to_prompt_nodes(str, &(*prompt_nodes), REDIRECT_APPEND);
	else
	{
		if (ft_strlen(str) < 4)
			return (free(str), print_errors_dup(">", *prompt_nodes), 1);
		else
			return (free(str), print_errors_dup(">>", *prompt_nodes), 1);
	}
	return (0);
}

int	split_input_redirection(int *i, char *prompt, t_prompt_nodes **prompt_nodes)
{
	char	*temp;
	char	*str;

	str = NULL;
	while (prompt[*i] == '<')
	{
		temp = (char *)malloc(2 * sizeof(char));
		temp[0] = prompt[*i];
		temp[1] = '\0';
		str = ft_strjoin2(str, temp);
		free(temp);
		*i = *i + 1;
	}
	if (ft_strlen(str) == 1)
		add_to_prompt_nodes(str, &(*prompt_nodes), REDIRECT_INPUT);
	else if (ft_strlen(str) == 2)
		add_to_prompt_nodes(str, &(*prompt_nodes), HEREDOC);
	else
	{
		if (ft_strlen(str) < 4)
			return (free(str), print_errors_dup("<", *prompt_nodes), 1);
		else
			return (free(str), print_errors_dup("<<", *prompt_nodes), 1);
	}
	return (0);
}
