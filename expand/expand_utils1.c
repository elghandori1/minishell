/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:52:52 by lissam            #+#    #+#             */
/*   Updated: 2024/05/26 16:03:52 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initexpand_vars(t_expand_norms *exp_v)
{
	exp_v->tmp = NULL;
	exp_v->i = 0;
	exp_v->j = 0;
	exp_v->k = 0;
	exp_v->str = NULL;
	exp_v->value = NULL;
	exp_v->tmp_str = NULL;
	exp_v->freestr = NULL;
	exp_v->tmp_env = NULL;
	exp_v->tmpvalue = NULL;
}

void	herdoc_case(t_expand_norms *exp_v)
{
	if (exp_v->tmp && exp_v->tmp->type == HEREDOC)
	{
		while (exp_v->tmp && exp_v->tmp->type != STRING)
		{
			exp_v->tmp = exp_v->tmp->next;
		}
		exp_v->tmp = exp_v->tmp->next;
	}
}

void	get_env_variable(t_expand_norms *exp_v)
{
	exp_v->tmp_env = g_lobal_env;
	while (exp_v->tmp_env)
	{
		if (ft_strcmp(exp_v->tmp_env->key, exp_v->value))
		{
			exp_v->tmp_env = exp_v->tmp_env->next;
		}
		else
		{
			exp_v->str = ft_strjoin2(exp_v->str, exp_v->tmp_env->value);
			break ;
		}
	}
}

void	count_dolars(t_expand_norms *exp_v)
{
	exp_v->j = 0;
	while (exp_v->tmp->string[exp_v->i] && exp_v->tmp->string[exp_v->i] == '$')
	{
		exp_v->j++;
		exp_v->i++;
	}
	if (exp_v->j % 2 == 0)
		even_number_dolar(exp_v);
	else
		odd_number_dolar(exp_v);
}

void	get_none_variables(t_expand_norms *exp_v)
{
	while (exp_v->tmp->string[exp_v->i] && exp_v->tmp->string[exp_v->i] != '$')
		exp_v->i++;
	if (exp_v->i > exp_v->j)
	{
		exp_v->freestr = ft_substr(exp_v->tmp->string, exp_v->j, exp_v->i
				- exp_v->j);
		exp_v->str = ft_strjoin2(exp_v->str, exp_v->freestr);
		free(exp_v->freestr);
		exp_v->freestr = NULL;
	}
}
