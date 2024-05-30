/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:51:52 by lissam            #+#    #+#             */
/*   Updated: 2024/05/26 16:03:49 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_odd_dolars(t_expand_norms *exp_v)
{
	while (exp_v->k < (exp_v->j - 1) / 2)
	{
		exp_v->str = ft_strjoin2(exp_v->str, "$");
		exp_v->k++;
	}
}

void	odd_number_dolar(t_expand_norms *exp_v)
{
	exp_v->k = 0;
	join_odd_dolars(exp_v);
	exp_v->j = 0;
	if (exp_v->tmp->string[exp_v->i] && ((exp_v->tmp->string[exp_v->i] >= 48
				&& exp_v->tmp->string[exp_v->i] <= 57)
			|| (exp_v->tmp->string[exp_v->i] >= 65
				&& exp_v->tmp->string[exp_v->i] <= 90)
			|| (exp_v->tmp->string[exp_v->i] >= 97
				&& exp_v->tmp->string[exp_v->i] <= 122)
			|| exp_v->tmp->string[exp_v->i] == '_'
			|| exp_v->tmp->string[exp_v->i] == '?'))
	{
		take_values(exp_v);
	}
	else
	{
		if (exp_v->tmp->next && exp_v->tmp->next->string[0] != 39
			&& exp_v->tmp->next->string[0] != 34)
			exp_v->str = ft_strjoin2(exp_v->str, "$");
		else if (exp_v->tmp->string[exp_v->i] == 39)
			exp_v->str = ft_strjoin2(exp_v->str, "$");
		else if (!exp_v->tmp->next)
			exp_v->str = ft_strjoin2(exp_v->str, "$");
	}
}

void	has_question_mark(t_expand_norms *exp_v)
{
	exp_v->j = 0;
	while (exp_v->value[exp_v->j] != '?')
		exp_v->j++;
	exp_v->tmp_str = ft_substr(exp_v->value, 0, exp_v->j);
	exp_v->tmp_env = g_lobal_env;
	while (exp_v->tmp_env)
	{
		if (ft_strcmp(exp_v->tmp_env->key, exp_v->tmp_str))
		{
			exp_v->tmp_env = exp_v->tmp_env->next;
		}
		else
		{
			exp_v->str = ft_strjoin2(exp_v->str, exp_v->tmp_env->value);
			break ;
		}
	}
	free(exp_v->tmp_str);
	exp_v->tmp_str = NULL;
	exp_v->value = exp_v->value + exp_v->j;
	exp_v->str = ft_strjoin2(exp_v->str, exp_v->value);
}

void	take_values(t_expand_norms *exp_v)
{
	get_value(exp_v);
	exp_v->tmpvalue = exp_v->value;
	if (exp_v->value[0] == '?')
		get_exit_status(exp_v);
	else if (ft_strchr(exp_v->value, '?'))
		has_question_mark(exp_v);
	else
		get_env_variable(exp_v);
	free(exp_v->tmpvalue);
	exp_v->tmpvalue = NULL;
	exp_v->value = NULL;
}

void	even_number_dolar(t_expand_norms *exp_v)
{
	exp_v->k = 0;
	while (exp_v->k < exp_v->j / 2)
	{
		exp_v->str = ft_strjoin2(exp_v->str, "$");
		exp_v->k++;
	}
	exp_v->j = 0;
	if (exp_v->tmp->string[exp_v->i] && ((exp_v->tmp->string[exp_v->i] >= 48
				&& exp_v->tmp->string[exp_v->i] <= 57)
			|| (exp_v->tmp->string[exp_v->i] >= 65
				&& exp_v->tmp->string[exp_v->i] <= 90)
			|| (exp_v->tmp->string[exp_v->i] >= 97
				&& exp_v->tmp->string[exp_v->i] <= 122)
			|| exp_v->tmp->string[exp_v->i] == '_'
			|| exp_v->tmp->string[exp_v->i] == '?'))
	{
		take_string_after_dolar(exp_v);
	}
}
