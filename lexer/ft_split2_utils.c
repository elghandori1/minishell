/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:05:17 by lissam            #+#    #+#             */
/*   Updated: 2024/05/27 09:05:48 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_inside_qoutes(char const *s, int *i)
{
	if (s[*i] && (s[*i] == 39 || s[*i] == 34))
	{
		if (s[*i] && s[*i] == 39)
		{
			*i = *i + 1;
			while (s[*i] && s[*i] != 39)
				*i = *i + 1;
		}
		else if (s[*i] && s[*i] == 34)
		{
			*i = *i + 1;
			while (s[*i] && s[*i] != 34)
				*i = *i + 1;
		}
	}
}

void	get_word_with_qoutes(char const *s, int *i)
{
	if (s[*i] && s[*i] == 39)
	{
		*i = *i + 1;
		while (s[*i] && s[*i] != 39)
			*i = *i + 1;
		*i = *i + 1;
	}
	else if (s[*i] && s[*i] == 34)
	{
		*i = *i + 1;
		while (s[*i] && s[*i] != 34)
			*i = *i + 1;
		*i = *i + 1;
	}
}
