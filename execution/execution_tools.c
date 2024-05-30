/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:29:41 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/23 14:29:42 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	stdin_stdout(t_cmd *std, int *tmpout, int *tmpint)
{
	t_cmd	*tm;

	tm = std;
	while (tm != NULL)
	{
		if ((tm->files) && ((tm->files->type == REDIRECT_OUTPUT)
				|| (tm->files->type == REDIRECT_APPEND)))
		{
			*tmpint = dup(0);
			*tmpout = dup(1);
			return (1);
		}
		else if ((tm->files) && ((tm->files->type == REDIRECT_INPUT)
				|| (tm->files->type == HEREDOC)))
		{
			*tmpint = dup(0);
			*tmpout = dup(1);
			return (1);
		}
		tm = tm->next;
	}
	return (0);
}

int	check_pipe(t_cmd *pi)
{
	t_cmd	*tmpi;

	tmpi = pi;
	if (tmpi->next != NULL)
		return (1);
	return (0);
}

int	count_heredoc(t_cmd *hrdc)
{
	t_cmd					*tc;
	int						herdoc_count;
	t_files_redirections	*fl;

	tc = hrdc;
	herdoc_count = 0;
	while (tc)
	{
		fl = tc->files;
		while (fl)
		{
			if (fl->type == HEREDOC)
				herdoc_count++;
			fl = fl->next;
		}
		tc = tc->next;
	}
	return (herdoc_count);
}

int	ambiguous(t_cmd *ambig)
{
	t_cmd	*ambigtmp;

	ambigtmp = ambig;
	while (ambigtmp != NULL)
	{
		if ((ambigtmp->files) && (ft_strchr(ambigtmp->files->file, ' ') != NULL
				|| ft_strchr(ambigtmp->files->file, '\t') != NULL))
		{
			return (1);
		}
		ambigtmp = ambigtmp->next;
	}
	return (0);
}
