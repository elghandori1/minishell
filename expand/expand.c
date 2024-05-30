/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:51:43 by lissam            #+#    #+#             */
/*   Updated: 2024/05/26 15:59:21 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	take_string_after_dolar(t_expand_norms *exp_v)
{
	exp_v->j = exp_v->i;
	while (exp_v->tmp->string[exp_v->i] && ((exp_v->tmp->string[exp_v->i] >= 48
				&& exp_v->tmp->string[exp_v->i] <= 57)
			|| (exp_v->tmp->string[exp_v->i] >= 65
				&& exp_v->tmp->string[exp_v->i] <= 90)
			|| (exp_v->tmp->string[exp_v->i] >= 97
				&& exp_v->tmp->string[exp_v->i] <= 122)
			|| exp_v->tmp->string[exp_v->i] == '_'
			|| exp_v->tmp->string[exp_v->i] == '?'))
	{
		exp_v->i++;
	}
	exp_v->freestr = ft_substr(exp_v->tmp->string, exp_v->j, exp_v->i
			- exp_v->j);
	exp_v->str = ft_strjoin2(exp_v->str, exp_v->freestr);
	free(exp_v->freestr);
	exp_v->freestr = NULL;
}

void	get_value(t_expand_norms *exp_v)
{
	exp_v->j = exp_v->i;
	while (exp_v->tmp->string[exp_v->i] && ((exp_v->tmp->string[exp_v->i] >= 48
				&& exp_v->tmp->string[exp_v->i] <= 57)
			|| (exp_v->tmp->string[exp_v->i] >= 65
				&& exp_v->tmp->string[exp_v->i] <= 90)
			|| (exp_v->tmp->string[exp_v->i] >= 97
				&& exp_v->tmp->string[exp_v->i] <= 122)
			|| exp_v->tmp->string[exp_v->i] == '_'
			|| exp_v->tmp->string[exp_v->i] == '?'))
	{
		exp_v->i++;
	}
	exp_v->value = ft_substr(exp_v->tmp->string, exp_v->j, exp_v->i - exp_v->j);
}

void	get_exit_status(t_expand_norms *exp_v)
{
	exp_v->tmp_env = g_lobal_env;
	exp_v->freestr = ft_itoa(exp_v->tmp_env->status);
	exp_v->str = ft_strjoin2(exp_v->str, exp_v->freestr);
	free(exp_v->freestr);
	exp_v->freestr = NULL;
	exp_v->value = exp_v->value + 1;
	exp_v->str = ft_strjoin2(exp_v->str, exp_v->value);
}

void	start_expand(t_expand_norms *exp_v)
{
	exp_v->i = 0;
	while (exp_v->tmp->string[exp_v->i])
	{
		exp_v->j = exp_v->i;
		get_none_variables(exp_v);
		if (exp_v->tmp->string[exp_v->i] && exp_v->tmp->string[exp_v->i] == '$')
		{
			count_dolars(exp_v);
		}
	}
	free(exp_v->tmp->string);
	if (exp_v->str)
		exp_v->tmp->string = exp_v->str;
	else
	{
		exp_v->tmp_str = malloc(1);
		exp_v->tmp_str[0] = '\0';
		exp_v->tmp->string = exp_v->tmp_str;
	}
	exp_v->str = NULL;
}

void	expanding(t_prompt_nodes *p)
{
	t_expand_norms	exp_v;

	initexpand_vars(&exp_v);
	exp_v.tmp = p;
	while (exp_v.tmp)
	{
		herdoc_case(&exp_v);
		if (exp_v.tmp && exp_v.tmp->type == STRING)
		{
			if (ft_strchr(exp_v.tmp->string, '$') && exp_v.tmp->string[0] != 39)
			{
				start_expand(&exp_v);
			}
		}
		if (exp_v.tmp)
			exp_v.tmp = exp_v.tmp->next;
	}
}

// void	expanding(t_prompt_nodes *p)
// {
// 	t_prompt_nodes	*tmp;
// 	int				i;
// 	int				j;
// 	int				k;
// 	char			*str;
// 	char			*value;
// 	char			*tmp_str;
// 	char 			*freestr;
// 	t_env			*tmp_env;
// 	char *tmpvalue;

// 	tmp = p;
// 	str = NULL;
// 	tmp_str = NULL;
// 	value = NULL;
// 	freestr = NULL;
// 	while (tmp)
// 	{
// 		if (tmp && tmp->type == HEREDOC)
// 		{
// 			while (tmp && tmp->type != STRING)
// 			{
// 				tmp = tmp->next;
// 			}
// 			tmp = tmp->next;
// 		}
// 		if (tmp && tmp->type == STRING)
// 		{
// 			if (ft_strchr(tmp->string, '$') && tmp->string[0] != 39)
// 			{
// 				i = 0;
// 				while (tmp->string[i])
// 				{
// 					j = i;
// 					while (tmp->string[i] && tmp->string[i] != '$')
// 						i++;
// 					if (i > j)
// 					{
// 						freestr = ft_substr(tmp->string, j, i- j);
// 						str = ft_strjoin2(str,freestr );
// 						free(freestr);
// 						freestr = NULL;
// 					}
// 					if (tmp->string[i] && tmp->string[i] == '$')
// 					{
// 						j = 0;
// 						while (tmp->string[i] && tmp->string[i] == '$')
// 						{
// 							j++;
// 							i++;
// 						}
// 						if (j % 2 == 0)
// 						{
// 							k = 0;
// 							while (k < j / 2)
// 							{
// 								str = ft_strjoin2(str, "$");
// 								k++;
// 							}
// 							j = 0;
// 							if (tmp->string[i]
// 								&& ((tmp->string[i] >= 48
// && tmp->string[i] <= 57)
// 								|| (tmp->string[i] >= 65
// && tmp->string[i] <= 90)
// 								|| (tmp->string[i] >= 97
// && tmp->string[i] <= 122)
// 								|| tmp->string[i] == '_'
// 								|| tmp->string[i] == '?'))
// 							{
// 								j = i;
// 								while (tmp->string[i]
// 								&& ((tmp->string[i] >= 48
// && tmp->string[i] <= 57)
// 								|| (tmp->string[i] >= 65
// && tmp->string[i] <= 90)
// 								|| (tmp->string[i] >= 97
// && tmp->string[i] <= 122)
// 								|| tmp->string[i] == '_'
// 								|| tmp->string[i] == '?'))
// 								{
// 									i++;
// 								}
// 								freestr = ft_substr(tmp->string, j,i - j);
// 								str = ft_strjoin2(str, freestr);
// 								free(freestr);
// 								freestr = NULL;
// 							}
// 						}
// 						else
// 						{
// 							k = 0;
// 							while (k < (j - 1) / 2)
// 							{
// 								str = ft_strjoin2(str, "$");

// 								k++;
// 							}
// 							j = 0;
// 							if (tmp->string[i]
// 								&& ((tmp->string[i] >= 48
// && tmp->string[i] <= 57)
// 								|| (tmp->string[i] >= 65
// && tmp->string[i] <= 90)
// 								|| (tmp->string[i] >= 97
// && tmp->string[i] <= 122)
// 								|| tmp->string[i] == '_'
// 								|| tmp->string[i] == '?'))
// 							{
// 								j = i;
// 								while (tmp->string[i]
// 								&& ((tmp->string[i] >= 48
// && tmp->string[i] <= 57)
// 								|| (tmp->string[i] >= 65
// && tmp->string[i] <= 90)
// 								|| (tmp->string[i] >= 97
// && tmp->string[i] <= 122)
// 								|| tmp->string[i] == '_'
// 								|| tmp->string[i] == '?'))
// 								{
// 									i++;
// 								}
// 								value = ft_substr(tmp->string, j, i - j);
// 								tmpvalue = value;
// 								if(value[0] == '?')
//                                 {
//                                     tmp_env = g_lobal_env;
// 									freestr  = ft_itoa(tmp_env->status);
//                                     str  = ft_strjoin2(str, freestr);
// 									free(freestr);
// 									freestr = NULL;
//                                     value = value + 1;
//                                     str = ft_strjoin2(str, value);
//                                 }
//                                 else if(ft_strchr(value, '?'))
//                                 {
//                                     int j;
//                                     j = 0;

//                                     while (value[j] != '?')
//                                     {
//                                         j++;
//                                     }

// 									tmp_str = ft_substr(value , 0 , j);
// 									tmp_env = g_lobal_env;
// 									while (tmp_env)
// 									{
// 										if (ft_strcmp(tmp_env->key, tmp_str))
// 										{
// 											tmp_env = tmp_env->next;
// 										}
// 										else
// 										{
// 											str = ft_strjoin2(str,
// tmp_env->value);
// 											break ;
// 										}
// 									}
// 									free(tmp_str);
// 									tmp_str = NULL;
//                                     value = value + j;
//                                     str = ft_strjoin2(str, value);
//                                 }
// 								else
// 								{
// 									tmp_env = g_lobal_env;
// 									while (tmp_env)
// 									{
// 										if (ft_strcmp(tmp_env->key, value))
// 										{
// 											tmp_env = tmp_env->next;
// 										}
// 										else
// 										{
// 											str = ft_strjoin2(str,
// tmp_env->value);
// 											break ;
// 										}
// 									}
// 								}
// 								free(tmpvalue);
// 								tmpvalue = NULL;
// 								value = NULL;
// 							}
// 							else
// 							{
// 								if(tmp->next && tmp->next->string[0] != 39
// && tmp->next->string[0] != 34)
// 									str = ft_strjoin2(str, "$");
// 								else if(tmp->string[i] == 39)
// 									str = ft_strjoin2(str, "$");
// 								else if(!tmp->next)
// 									str = ft_strjoin2(str, "$");
// 							}
// 						}
// 					}
// 				}
// 				free(tmp->string);
// 				if (str)
// 					tmp->string = str;
// 				else
// 				{
// 					tmp_str = malloc(1);
// 					tmp_str[0] = '\0';
// 					tmp->string = tmp_str;
// 				}
// 				str = NULL;
// 			}
// 		}
// 		if (tmp)
// 			tmp = tmp->next;
// 	}
// }