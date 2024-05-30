/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:00:53 by lissam            #+#    #+#             */
/*   Updated: 2024/05/26 17:14:41 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_quotes(char *type_quotes, t_prompt_nodes **head)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putstr_fd(type_quotes, 2);
	ft_putstr_fd("'\n", 2);
	g_lobal_env->status = 2;
	free_prompt_nodes(*head);
}

int	redirections_and_pipe(int *i, char *prompt, t_prompt_nodes **prompt_nodes)
{
	if (prompt[*i] == '>')
	{
		if (split_output_redirection(i, prompt, prompt_nodes) == 1)
			return (1);
	}
	skip_spaces(prompt, i, prompt_nodes);
	if (prompt[*i] == '<')
	{
		if (split_input_redirection(i, prompt, prompt_nodes) == 1)
			return (1);
	}
	skip_spaces(prompt, i, prompt_nodes);
	if (prompt[*i] == '|')
	{
		if (split_pipe(i, prompt, prompt_nodes) == 1)
			return (1);
	}
	return (0);
}

int	quotes(int *i, char *prompt, t_prompt_nodes **prompt_nodes)
{
	if (prompt[*i] == 34)
	{
		if (split_double_quotes(i, prompt, prompt_nodes) == 1)
			return (print_error_quotes("\"", prompt_nodes), 1);
	}
	skip_spaces(prompt, i, prompt_nodes);
	if (prompt[*i] == 39)
	{
		if (split_single_quote(i, prompt, prompt_nodes) == 1)
			return (print_error_quotes("\'", prompt_nodes), 1);
	}
	return (0);
}

t_cmd	*lexer(char *prmt)
{
	t_prompt_nodes	*p;
	int				i;

	i = 0;
	p = NULL;
	skip_first_spaces(prmt, &i);
	while (prmt[i])
	{
		skip_spaces(prmt, &i, &p);
		if (prmt[i] != '>' && prmt[i] != '<' && prmt[i] != '|' && prmt[i] != ' '
			&& (prmt[i] > 13 || prmt[i] < 9) && prmt[i] != 34 && prmt[i] != 39
			&& prmt[i] != '\0')
			split_chars(&i, prmt, &p);
		skip_spaces(prmt, &i, &p);
		if (prmt[i] == '>' || prmt[i] == '<' || prmt[i] == '|')
			if (redirections_and_pipe(&i, prmt, &p) == 1)
				return (NULL);
		skip_spaces(prmt, &i, &p);
		if (prmt[i] == 34 || prmt[i] == 39)
			if (quotes(&i, prmt, &p) == 1)
				return (NULL);
	}
	if (syntax_error(p) == 1)
		return (NULL);
	return (actions(p));
}
