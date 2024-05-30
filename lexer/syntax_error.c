/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:11:22 by lissam            #+#    #+#             */
/*   Updated: 2024/05/27 08:58:18 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_errors(t_prompt_nodes *tm)
{
	if (!tm->next || (tm->next && tm->next->type == PIPE))
		return (print_errors_token("|"), 1);
	else if (tm->next && tm->next->type == WHITE_SPACE)
	{
		if (!tm->next->next || (tm->next->next && tm->next->next->type == PIPE))
			return (print_errors_token("|"), 1);
	}
	return (0);
}

int	redirections_errors(t_prompt_nodes *tm)
{
	if (!tm->next || (tm->next && tm->next->type == WHITE_SPACE
			&& !tm->next->next))
		return (print_errors_token("newline"), 1);
	if (!tm->next || (tm->next && tm->next->type != STRING
			&& tm->next->type != WHITE_SPACE))
		return (print_errors_token(tm->next->string), 1);
	else if (tm->next && tm->next->type == WHITE_SPACE)
	{
		if (tm->next->next && tm->next->next->type != STRING
			&& tm->next->next->type != WHITE_SPACE)
			return (print_errors_token(tm->next->next->string), 1);
	}
	return (0);
}

int	check(t_prompt_nodes *tm, t_prompt_nodes *prompt_nodes)
{
	if (tm->type == PIPE)
		if (pipe_errors(tm) == 1)
			return (free_prompt_nodes(prompt_nodes), 1);
	if (tm->type == REDIRECT_INPUT)
		if (redirections_errors(tm) == 1)
			return (free_prompt_nodes(prompt_nodes), 1);
	if (tm->type == REDIRECT_OUTPUT)
		if (redirections_errors(tm) == 1)
			return (free_prompt_nodes(prompt_nodes), 1);
	if (tm->type == REDIRECT_APPEND)
		if (redirections_errors(tm) == 1)
			return (free_prompt_nodes(prompt_nodes), 1);
	if (tm->type == HEREDOC)
		if (redirections_errors(tm) == 1)
			return (free_prompt_nodes(prompt_nodes), 1);
	return (0);
}

int	syntax_error(t_prompt_nodes *prompt_nodes)
{
	t_prompt_nodes	*tm;

	tm = prompt_nodes;
	if (tm && tm->type == PIPE)
	{
		free_prompt_nodes(prompt_nodes);
		return (print_errors_token("|"), 1);
	}
	while (tm)
	{
		if (check(tm, prompt_nodes) == 1)
			return (1);
		tm = tm->next;
	}
	return (0);
}
