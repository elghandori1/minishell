/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:26:06 by lissam            #+#    #+#             */
/*   Updated: 2024/05/26 16:44:38 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirection_input(t_norms_get_cmd *gcmd_v)
{
	gcmd_v->tmpfiles->type = REDIRECT_INPUT;
	gcmd_v->tmp = gcmd_v->tmp->next;
	if (gcmd_v->tmp->type == WHITE_SPACE)
		gcmd_v->tmp = gcmd_v->tmp->next;
	gcmd_v->tmpstr = NULL;
	while (gcmd_v->tmp && gcmd_v->tmp->type == STRING)
	{
		gcmd_v->free_str = ft_strdup(gcmd_v->tmp->string);
		gcmd_v->tmpstr = ft_strjoin2(gcmd_v->tmpstr, gcmd_v->free_str);
		free(gcmd_v->free_str);
		gcmd_v->free_str = NULL;
		if (gcmd_v->tmp->next && gcmd_v->tmp->next->type != STRING)
			break ;
		gcmd_v->tmp = gcmd_v->tmp->next;
	}
	gcmd_v->tmpfiles->file = gcmd_v->tmpstr;
	if (gcmd_v->tmpfiles->file && (gcmd_v->tmpfiles->file[0] == 39
			|| gcmd_v->tmpfiles->file[0] == 34))
		gcmd_v->tmpfiles->qouted = 1;
	gcmd_v->tmpstr = NULL;
}

void	redirection_output(t_norms_get_cmd *gcmd_v)
{
	gcmd_v->tmpfiles->type = REDIRECT_OUTPUT;
	gcmd_v->tmp = gcmd_v->tmp->next;
	if (gcmd_v->tmp->type == WHITE_SPACE)
		gcmd_v->tmp = gcmd_v->tmp->next;
	gcmd_v->tmpstr = NULL;
	while (gcmd_v->tmp && gcmd_v->tmp->type == STRING)
	{
		gcmd_v->free_str = ft_strdup(gcmd_v->tmp->string);
		gcmd_v->tmpstr = ft_strjoin2(gcmd_v->tmpstr, gcmd_v->free_str);
		free(gcmd_v->free_str);
		gcmd_v->free_str = NULL;
		if (gcmd_v->tmp->next && gcmd_v->tmp->next->type != STRING)
			break ;
		gcmd_v->tmp = gcmd_v->tmp->next;
	}
	gcmd_v->tmpfiles->file = gcmd_v->tmpstr;
	if (gcmd_v->tmpfiles->file && (gcmd_v->tmpfiles->file[0] == 39
			|| gcmd_v->tmpfiles->file[0] == 34))
		gcmd_v->tmpfiles->qouted = 1;
	gcmd_v->tmpstr = NULL;
}

void	redirection_append(t_norms_get_cmd *gcmd_v)
{
	gcmd_v->tmpfiles->type = REDIRECT_APPEND;
	gcmd_v->tmp = gcmd_v->tmp->next;
	if (gcmd_v->tmp->type == WHITE_SPACE)
		gcmd_v->tmp = gcmd_v->tmp->next;
	gcmd_v->tmpstr = NULL;
	while (gcmd_v->tmp && gcmd_v->tmp->type == STRING)
	{
		gcmd_v->free_str = ft_strdup(gcmd_v->tmp->string);
		gcmd_v->tmpstr = ft_strjoin2(gcmd_v->tmpstr, gcmd_v->free_str);
		free(gcmd_v->free_str);
		gcmd_v->free_str = NULL;
		if (gcmd_v->tmp->next && gcmd_v->tmp->next->type != STRING)
			break ;
		gcmd_v->tmp = gcmd_v->tmp->next;
	}
	gcmd_v->tmpfiles->file = gcmd_v->tmpstr;
	if (gcmd_v->tmpfiles->file && (gcmd_v->tmpfiles->file[0] == 39
			|| gcmd_v->tmpfiles->file[0] == 34))
		gcmd_v->tmpfiles->qouted = 1;
	gcmd_v->tmpstr = NULL;
}

void	free__null(t_norms_get_cmd *gcmd_v)
{
	free(gcmd_v->pindex);
	free(gcmd_v->tty);
	gcmd_v->tmpstr = NULL;
}

void	herdoc(t_norms_get_cmd *gcmd_v)
{
	gcmd_v->tmpfiles->type = HEREDOC;
	gcmd_v->tmp = gcmd_v->tmp->next;
	if (gcmd_v->tmp->type == WHITE_SPACE)
		gcmd_v->tmp = gcmd_v->tmp->next;
	gcmd_v->tmpstr = NULL;
	while (gcmd_v->tmp && gcmd_v->tmp->type == STRING)
	{
		gcmd_v->free_str = ft_strdup(gcmd_v->tmp->string);
		gcmd_v->tmpstr = ft_strjoin2(gcmd_v->tmpstr, gcmd_v->free_str);
		free(gcmd_v->free_str);
		gcmd_v->free_str = NULL;
		if (gcmd_v->tmp->next && gcmd_v->tmp->next->type != STRING)
			break ;
		gcmd_v->tmp = gcmd_v->tmp->next;
	}
	gcmd_v->tmpfiles->limiter = gcmd_v->tmpstr;
	if (gcmd_v->tmpfiles->limiter && (gcmd_v->tmpfiles->limiter[0] == 39
			|| gcmd_v->tmpfiles->limiter[0] == 34))
		gcmd_v->tmpfiles->qouted = 1;
	gcmd_v->tmpfile = ft_strdup("/tmp/heredoc_");
	gcmd_v->pindex = ft_itoa(gcmd_v->tmpcmds->processindex);
	gcmd_v->tty = correcttty(ttyname(0));
	gcmd_v->tmpfiles->file = ft_strjoin2(ft_strjoin2(gcmd_v->tmpfile,
				gcmd_v->pindex), gcmd_v->tty);
	free__null(gcmd_v);
}
