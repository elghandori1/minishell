/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:24:43 by lissam            #+#    #+#             */
/*   Updated: 2024/05/28 09:50:35 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*correcttty(char *ttyname)
{
	char	*newttyname;
	int		i;
	int		index;

	newttyname = ft_calloc(ft_strlen(ttyname) + 1, 1);
	i = 0;
	index = 0;
	while (ttyname[i])
	{
		if (ttyname[i] != '/')
		{
			newttyname[index] = ttyname[i];
			index++;
		}
		i++;
	}
	return (newttyname);
}

void	take_cmds(t_norms_get_cmd *gcmd_v)
{
	while (gcmd_v->tmp && gcmd_v->tmp->type != WHITE_SPACE
		&& gcmd_v->tmp->type != REDIRECT_INPUT
		&& gcmd_v->tmp->type != REDIRECT_OUTPUT
		&& gcmd_v->tmp->type != REDIRECT_APPEND && gcmd_v->tmp->type != HEREDOC
		&& gcmd_v->tmp->type != PIPE)
	{
		gcmd_v->free_str = ft_strdup(gcmd_v->tmp->string);
		gcmd_v->tmpstr = ft_strjoin2(gcmd_v->tmpstr, gcmd_v->free_str);
		free(gcmd_v->free_str);
		gcmd_v->free_str = NULL;
		if (gcmd_v->tmp->next && gcmd_v->tmp->next->type != STRING)
			break ;
		gcmd_v->tmp = gcmd_v->tmp->next;
	}
	gcmd_v->str = ft_strjoin2(gcmd_v->str, " ");
	if (!gcmd_v->tmpstr)
	{
		gcmd_v->str = ft_strjoin2(gcmd_v->str, "");
	}
	else
	{
		gcmd_v->str = ft_strjoin2(gcmd_v->str, gcmd_v->tmpstr);
	}
	free(gcmd_v->tmpstr);
	gcmd_v->tmpstr = NULL;
}

void	check_types(t_norms_get_cmd *gcmd_v)
{
	if (gcmd_v->tmp && gcmd_v->tmp->type != REDIRECT_INPUT
		&& gcmd_v->tmp->type != REDIRECT_OUTPUT
		&& gcmd_v->tmp->type != REDIRECT_APPEND && gcmd_v->tmp->type != HEREDOC
		&& gcmd_v->tmp->type != PIPE)
		take_cmds(gcmd_v);
	if (gcmd_v->tmp && (gcmd_v->tmp->type == REDIRECT_INPUT
			|| gcmd_v->tmp->type == REDIRECT_OUTPUT
			|| gcmd_v->tmp->type == REDIRECT_APPEND
			|| gcmd_v->tmp->type == HEREDOC))
	{
		gcmd_v->tmpfiles = lst_new4();
		if (gcmd_v->tmp->type == REDIRECT_INPUT)
			redirection_input(gcmd_v);
		else if (gcmd_v->tmp->type == REDIRECT_OUTPUT)
			redirection_output(gcmd_v);
		else if (gcmd_v->tmp->type == REDIRECT_APPEND)
			redirection_append(gcmd_v);
		else if (gcmd_v->tmp->type == HEREDOC)
			herdoc(gcmd_v);
		ft_lstadd_back4(&gcmd_v->tmpcmds->files, gcmd_v->tmpfiles);
	}
	if (gcmd_v->tmp)
		gcmd_v->tmp = gcmd_v->tmp->next;
}

void	set_null(t_norms_get_cmd *gcmd_v)
{
	gcmd_v->str = NULL;
	gcmd_v->tmpcmds = NULL;
	gcmd_v->tmpstr = NULL;
}

t_cmd	*get_cmds(t_prompt_nodes *p)
{
	t_norms_get_cmd			gcmd_v;

	init_get_cmd_variables(&gcmd_v);
	gcmd_v.tmp = p;
	while (gcmd_v.tmp)
	{
		gcmd_v.tmpcmds = lst_new3();
		gcmd_v.tmpcmds->processindex = gcmd_v.index++;
		gcmd_v.tmpfiles = NULL;
		while (gcmd_v.tmp && gcmd_v.tmp->type != PIPE)
			check_types(&gcmd_v);
		gcmd_v.tmpcmds->args = ft_split2(gcmd_v.str, ' ');
		if (gcmd_v.tmpcmds->args)
			gcmd_v.tmpcmds->cmd = gcmd_v.tmpcmds->args[0];
		else
			gcmd_v.tmpcmds->cmd = NULL;
		ft_lstadd_back3(&gcmd_v.cmds, gcmd_v.tmpcmds);
		free(gcmd_v.str);
		set_null(&gcmd_v);
		if (gcmd_v.tmp)
			gcmd_v.tmp = gcmd_v.tmp->next;
	}
	quotes_remover(gcmd_v.cmds);
	return (gcmd_v.cmds);
}
