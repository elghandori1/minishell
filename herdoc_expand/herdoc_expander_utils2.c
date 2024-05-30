/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expander_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:21:24 by lissam            #+#    #+#             */
/*   Updated: 2024/05/27 09:29:23 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_value(t_herdocexp_v *hev)
{
	hev->tmp_env = g_lobal_env;
	hev->free_str = ft_itoa(hev->tmp_env->status);
	hev->str = ft_strjoin2(hev->str, hev->free_str);
	free(hev->free_str);
	hev->free_str = NULL;
	hev->value = hev->value + 1;
	hev->str = ft_strjoin2(hev->str, hev->value);
}

void	get_string_value(t_herdocexp_v *hev, char *herdoc_str)
{
	hev->j = hev->i;
	while (herdoc_str[hev->i] && ((herdoc_str[hev->i] >= 48
				&& herdoc_str[hev->i] <= 57) || (herdoc_str[hev->i] >= 65
				&& herdoc_str[hev->i] <= 90) || (herdoc_str[hev->i] >= 97
				&& herdoc_str[hev->i] <= 122) || herdoc_str[hev->i] == '_'
			|| herdoc_str[hev->i] == '?'))
	{
		hev->i++;
	}
	hev->value = ft_substr(herdoc_str, hev->j, hev->i - hev->j);
}

void	get_value_before_dolar(t_herdocexp_v *hev)
{
	hev->j = 0;
	while (hev->value[hev->j] != '?')
		hev->j++;
	hev->tmp_str = ft_substr(hev->value, 0, hev->j);
	hev->tmp_env = g_lobal_env;
	while (hev->tmp_env)
	{
		if (ft_strcmp(hev->tmp_env->key, hev->tmp_str))
			hev->tmp_env = hev->tmp_env->next;
		else
		{
			hev->str = ft_strjoin2(hev->str, hev->tmp_env->value);
			break ;
		}
	}
	free(hev->tmp_str);
	hev->tmp_str = NULL;
	hev->value = hev->value + hev->j;
	hev->str = ft_strjoin2(hev->str, hev->value);
}

void	get_env_value(t_herdocexp_v *hev)
{
	hev->tmp_env = g_lobal_env;
	while (hev->tmp_env)
	{
		if (ft_strcmp(hev->tmp_env->key, hev->value))
		{
			hev->tmp_env = hev->tmp_env->next;
		}
		else
		{
			hev->str = ft_strjoin2(hev->str, hev->tmp_env->value);
			break ;
		}
	}
}
