/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:39:48 by lissam            #+#    #+#             */
/*   Updated: 2024/05/27 14:40:43 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_inside_single(t_remover_norms *remover_n, char *str)
{
	remover_n->substr = ft_substr(str, remover_n->j, remover_n->i
			- remover_n->j);
	remover_n->tmp_str = ft_strjoin2(remover_n->tmp_str, remover_n->substr);
	free(remover_n->substr);
	remover_n->substr = NULL;
}

void	get_inside_double(t_remover_norms *remover_n, char *str)
{
	remover_n->substr = ft_substr(str, remover_n->j, remover_n->i
			- remover_n->j);
	remover_n->tmp_str = ft_strjoin2(remover_n->tmp_str, remover_n->substr);
	free(remover_n->substr);
	remover_n->substr = NULL;
}
