/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:49:18 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/26 11:44:09 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_stdout(t_files_redirections *files)
{
	while (files)
	{
		if (files->type == REDIRECT_OUTPUT || files->type == REDIRECT_APPEND)
			return (1);
		files = files->next;
	}
	return (0);
}

int	check_stdin(t_files_redirections *files)
{
	while (files)
	{
		if (files->type == REDIRECT_INPUT || files->type == HEREDOC)
			return (1);
		files = files->next;
	}
	return (0);
}

void	run_stdout(t_files_redirections *files)
{
	int	fdout;

	while (files)
	{
		if (files->type == REDIRECT_OUTPUT || files->type == REDIRECT_APPEND)
		{
			fdout = open(files->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fdout == -1)
			{
				perror(files->file);
				exit(1);
			}
		}
		files = files->next;
	}
	dup2(fdout, 1);
}

void	run_stdin(t_files_redirections *files)
{
	int	fdin;

	while (files)
	{
		if (files->type == REDIRECT_INPUT || files->type == HEREDOC)
		{
			fdin = open(files->file, O_RDONLY);
			if (fdin == -1)
			{
				perror(files->file);
				exit(1);
			}
		}
		files = files->next;
	}
	dup2(fdin, 0);
}

void	wait_for_children(void)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_lobal_env->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				fprintf(stderr, "Quit: 3\n");
			g_lobal_env->status = 128 + WTERMSIG(status);
		}
	}
	if (g_lobal_env->status == 141)
		g_lobal_env->status = 127;
	set_status(g_lobal_env->status);
}
