/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:02:13 by lissam            #+#    #+#             */
/*   Updated: 2024/05/27 19:47:38 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	non_qouted(t_remover_norms *remover_n, char *str)
{
	remover_n->j = remover_n->i;
	while (str[remover_n->i] && str[remover_n->i] != '\''
		&& str[remover_n->i] != '\"')
		remover_n->i++;
	if (remover_n->i > remover_n->j)
	{
		remover_n->substr = ft_substr(str, remover_n->j, remover_n->i
				- remover_n->j);
		remover_n->tmp_str = ft_strjoin2(remover_n->tmp_str, remover_n->substr);
		free(remover_n->substr);
		remover_n->substr = NULL;
	}
}

void	single_qoute(t_remover_norms *remover_n, char *str)
{
	remover_n->i++;
	remover_n->j = remover_n->i;
	while (str[remover_n->i] && str[remover_n->i] != '\'')
		remover_n->i++;
	if (remover_n->i > remover_n->j)
		get_inside_single(remover_n, str);
	else
	{
		remover_n->empty = NULL;
		remover_n->empty = malloc(1 * sizeof(char));
		remover_n->empty[0] = '\0';
		if (remover_n->tmp_str)
		{
			remover_n->tmp_str = ft_strjoin2(remover_n->tmp_str,
					remover_n->empty);
			free(remover_n->empty);
			remover_n->empty = NULL;
		}
		else
			remover_n->tmp_str = remover_n->empty;
	}
	if (str[remover_n->i] == '\'')
		remover_n->i++;
}

void	double_qoutes(t_remover_norms *remover_n, char *str)
{
	remover_n->i++;
	remover_n->j = remover_n->i;
	while (str[remover_n->i] && str[remover_n->i] != '\"')
		remover_n->i++;
	if (remover_n->i > remover_n->j)
		get_inside_double(remover_n, str);
	else
	{
		remover_n->empty = NULL;
		remover_n->empty = malloc(1 * sizeof(char));
		remover_n->empty[0] = '\0';
		if (remover_n->tmp_str)
		{
			remover_n->tmp_str = ft_strjoin2(remover_n->tmp_str,
					remover_n->empty);
			free(remover_n->empty);
			remover_n->empty = NULL;
		}
		else
			remover_n->tmp_str = remover_n->empty;
	}
	if (str[remover_n->i] == '\"')
		remover_n->i++;
}

char	*remover(char *str)
{
	t_remover_norms	remover_n;

	init_remover_vars(&remover_n);
	while (str && str[remover_n.i])
	{
		non_qouted(&remover_n, str);
		if (str[remover_n.i] == '\'')
		{
			single_qoute(&remover_n, str);
		}
		if (str[remover_n.i] && str[remover_n.i] == '\"')
		{
			double_qoutes(&remover_n, str);
		}
	}
	return (remover_n.tmp_str);
}

void	quotes_remover(t_cmd *cmd)
{
	t_q_r_n	q_r;

	init_qoutes_remover_variables(&q_r, cmd);
	while (q_r.tmp_cmd)
	{
		q_r.str = remover(q_r.tmp_cmd->cmd);
		q_r.tmp_cmd->cmd = q_r.str;
		q_r.str = NULL;
		qouted_args(&q_r);
		qouted_files(&q_r);
		q_r.str = NULL;
		q_r.tmp_cmd = q_r.tmp_cmd->next;
	}
}
