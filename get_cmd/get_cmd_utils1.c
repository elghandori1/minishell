/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:25:34 by lissam            #+#    #+#             */
/*   Updated: 2024/05/26 16:44:38 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*lst_new3(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->args = NULL;
	new->files = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back3(t_cmd **node, t_cmd *new)
{
	t_cmd	*last;

	if (!node)
		return ;
	if (*node == NULL)
	{
		*node = new;
	}
	else
	{
		last = *node;
		while (last->next)
		{
			last = last->next;
		}
		last->next = new;
	}
}

t_files_redirections	*lst_new4(void)
{
	t_files_redirections	*new;

	new = (t_files_redirections *)malloc(sizeof(t_files_redirections));
	if (!new)
		return (NULL);
	new->file = NULL;
	new->type = -1;
	new->limiter = NULL;
	new->next = NULL;
	new->qouted = 0;
	return (new);
}

void	ft_lstadd_back4(t_files_redirections **node, t_files_redirections *new)
{
	t_files_redirections	*last;

	if (!node)
		return ;
	if (*node == NULL)
	{
		*node = new;
	}
	else
	{
		last = *node;
		while (last->next)
		{
			last = last->next;
		}
		last->next = new;
	}
}

void	init_get_cmd_variables(t_norms_get_cmd *gcmd_v)
{
	gcmd_v->tmpstr = NULL;
	gcmd_v->tmpfiles = NULL;
	gcmd_v->cmds = NULL;
	gcmd_v->str = NULL;
	gcmd_v->free_str = NULL;
	gcmd_v->tmpcmds = NULL;
	gcmd_v->index = 0;
	gcmd_v->tty = NULL;
	gcmd_v->pindex = NULL;
	gcmd_v->tmpfile = NULL;
	gcmd_v->tmp = NULL;
}
