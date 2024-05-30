/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:33:35 by lissam            #+#    #+#             */
/*   Updated: 2024/05/27 15:12:40 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_remover_vars(t_remover_norms *remover_n)
{
	remover_n->tmp_str = NULL;
	remover_n->empty = NULL;
	remover_n->substr = NULL;
	remover_n->i = 0;
	remover_n->j = 0;
}

void	init_qoutes_remover_variables(t_q_r_n *q_r, t_cmd *cmd)
{
	q_r->i = 0;
	q_r->tmp_cmd = cmd;
	q_r->str = NULL;
	q_r->fl = NULL;
}

void	qouted_args(t_q_r_n *q_r)
{
	if (q_r->tmp_cmd->args)
	{
		q_r->i = 0;
		while (q_r->tmp_cmd->args[q_r->i])
		{
			q_r->str = remover(q_r->tmp_cmd->args[q_r->i]);
			free(q_r->tmp_cmd->args[q_r->i]);
			q_r->tmp_cmd->args[q_r->i] = q_r->str;
			q_r->i++;
		}
	}
}

void	qouted_files(t_q_r_n *q_r)
{
	q_r->fl = q_r->tmp_cmd->files;
	while (q_r->fl)
	{
		q_r->str = remover(q_r->fl->file);
		free(q_r->fl->file);
		q_r->fl->file = q_r->str;
		q_r->str = NULL;
		q_r->str = remover(q_r->fl->limiter);
		free(q_r->fl->limiter);
		q_r->fl->limiter = q_r->str;
		q_r->fl = q_r->fl->next;
	}
}
