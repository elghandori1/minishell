/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expander_utils1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:19:48 by lissam            #+#    #+#             */
/*   Updated: 2024/05/28 09:51:02 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_variables_hexp(t_herdocexp_v *hev)
{
	hev->i = 0;
	hev->j = 0;
	hev->k = 0;
	hev->str = NULL;
	hev->tmp_env = NULL;
	hev->free_str = NULL;
	hev->value = NULL;
	hev->tmp_str = NULL;
	hev->tmp_value = NULL;
}

void	count_dolars_herdoc(t_herdocexp_v *hev, char *herdoc_str)
{
	while (herdoc_str[hev->i] && herdoc_str[hev->i] == '$')
	{
		hev->j++;
		hev->i++;
	}
}

void	even_dolars(t_herdocexp_v *hev, char *herdoc_str)
{
	hev->k = 0;
	while (hev->k < hev->j / 2)
	{
		hev->str = ft_strjoin2(hev->str, "$");
		hev->k++;
	}
	hev->j = 0;
	if (herdoc_str[hev->i] && ((herdoc_str[hev->i] >= 48
				&& herdoc_str[hev->i] <= 57) || (herdoc_str[hev->i] >= 65
				&& herdoc_str[hev->i] <= 90) || (herdoc_str[hev->i] >= 97
				&& herdoc_str[hev->i] <= 122) || herdoc_str[hev->i] == '_'
			|| herdoc_str[hev->i] == '?'))
	{
		hev->j = hev->i;
		while (herdoc_str[hev->i] && ((herdoc_str[hev->i] >= 48
					&& herdoc_str[hev->i] <= 57) || (herdoc_str[hev->i] >= 65
					&& herdoc_str[hev->i] <= 90) || (herdoc_str[hev->i] >= 97
					&& herdoc_str[hev->i] <= 122) || herdoc_str[hev->i] == '_'
				|| herdoc_str[hev->i] == '?'))
			hev->i++;
		hev->free_str = ft_substr(herdoc_str, hev->j, hev->i - hev->j);
		hev->str = ft_strjoin2(hev->str, hev->free_str);
		free(hev->free_str);
		hev->free_str = NULL;
	}
}

void	odd_dolars(t_herdocexp_v *hev, char *herdoc_str)
{
	hev->k = 0;
	while (hev->k < (hev->j - 1) / 2)
	{
		hev->str = ft_strjoin2(hev->str, "$");
		hev->k++;
	}
	if (herdoc_str[hev->i] == 34 || herdoc_str[hev->i] == 39)
		hev->str = ft_strjoin2(hev->str, "$");
	hev->j = 0;
	if (herdoc_str[hev->i] && ((herdoc_str[hev->i] >= 48
				&& herdoc_str[hev->i] <= 57) || (herdoc_str[hev->i] >= 65
				&& herdoc_str[hev->i] <= 90) || (herdoc_str[hev->i] >= 97
				&& herdoc_str[hev->i] <= 122) || herdoc_str[hev->i] == '_'
			|| herdoc_str[hev->i] == '?'))
	{
		actions_getting_values(hev, herdoc_str);
	}
	else
	{
		if (herdoc_str && herdoc_str[hev->i] == 39 && herdoc_str[hev->i] == 34)
			hev->str = ft_strjoin2(hev->str, "$");
	}
}
