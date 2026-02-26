/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_tools3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:32:03 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/26 20:45:24 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pipe_error(void)
{
	perror("pipe");
	set_status(1);
	exit(1);
}

void	handle_builtin_with_files(t_cmd *cmd, int *tmpout, int *tmpint)
{
	int	fdd;

	fdd = 0;
	if (stdin_stdout(cmd, tmpout, tmpint))
	{
		fdd = start_std(cmd);
		if (fdd == -1)
			printf("%s: No such file or directory\n", cmd->files->file);
		else
			run_builtin(cmd);
	}
	if (cmd->files != NULL)
		restore_fd(*tmpout, *tmpint);
}

void	handle_builtin_pipe(t_cmd *cmd, int *input_fd, int fd[2])
{
	int	tmpout;
	int	tmpint;

	tmpout = dup(STDOUT_FILENO);
	tmpint = dup(STDIN_FILENO);
	if (*input_fd != STDIN_FILENO)
		dup2(*input_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	run_builtin(cmd);
	restore_fd(tmpout, tmpint);
}

void	process_command(t_cmd *cmd, int *input_fd, int fd[2])
{
	int	tmpout;
	int	tmpint;

	tmpout = 0;
	tmpint = 0;
	if (is_builtin(cmd->cmd))
	{
		if (check_stdout(cmd->files) || check_stdin(cmd->files))
			handle_builtin_with_files(cmd, &tmpout, &tmpint);
		else
			handle_builtin_pipe(cmd, input_fd, fd);
	}
	else
		run_pipeline(cmd, *input_fd, fd[1], fd);
	close(fd[1]);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	*input_fd = fd[0];
}

void	finalize_pipeline(t_cmd *cmd, int input_fd)
{
	if (!check_builts(cmd))
	{
		run_pipeline(cmd, input_fd, STDOUT_FILENO, NULL);
	}
	if (input_fd != STDIN_FILENO)
	{
		close(input_fd);
	}
	wait_for_children();
	if (is_builtin(cmd->cmd))
	{
		set_status(0);
	}
}
