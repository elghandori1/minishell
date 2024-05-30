/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:14:25 by lissam            #+#    #+#             */
/*   Updated: 2024/05/26 17:14:54 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*actions(t_prompt_nodes *p)
{
	t_cmd	*cmd;

	expanding(p);
	cmd = get_cmds(p);
	free_prompt_nodes(p);
	return (cmd);
}

void	skip_first_spaces(char *prompt, int *i)
{
	while ((prompt[*i] >= 9 && prompt[*i] <= 13) || prompt[*i] == ' ')
		*i = *i + 1;
}
