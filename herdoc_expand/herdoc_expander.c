/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:02:21 by lissam            #+#    #+#             */
/*   Updated: 2024/05/27 09:21:07 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	actions_getting_values(t_herdocexp_v *hev, char *herdoc_str)
{
	get_string_value(hev, herdoc_str);
	hev->tmp_value = hev->value;
	if (hev->value[0] == '?')
		exit_value(hev);
	else if (ft_strchr(hev->value, '?'))
		get_value_before_dolar(hev);
	else
		get_env_value(hev);
	free(hev->tmp_value);
	hev->tmp_value = NULL;
	hev->value = NULL;
}

void	start_expanding_string(t_herdocexp_v *hev, char *herdoc_str)
{
	hev->j = hev->i;
	while (herdoc_str[hev->i] && herdoc_str[hev->i] != '$')
		hev->i++;
	if (hev->i > hev->j)
	{
		hev->free_str = ft_substr(herdoc_str, hev->j, hev->i - hev->j);
		hev->str = ft_strjoin2(hev->str, hev->free_str);
		free(hev->free_str);
		hev->free_str = NULL;
	}
	if (herdoc_str[hev->i] && herdoc_str[hev->i] == '$')
	{
		hev->j = 0;
		count_dolars_herdoc(hev, herdoc_str);
		if (hev->j % 2 == 0)
			even_dolars(hev, herdoc_str);
		else
			odd_dolars(hev, herdoc_str);
	}
}

char	*herdoc_expander(char *herdoc_str)
{
	t_herdocexp_v	hev;

	init_variables_hexp(&hev);
	if (ft_strchr(herdoc_str, '$'))
	{
		hev.i = 0;
		while (herdoc_str[hev.i])
		{
			start_expanding_string(&hev, herdoc_str);
		}
		return (hev.str);
	}
	else
		return (herdoc_str);
}
