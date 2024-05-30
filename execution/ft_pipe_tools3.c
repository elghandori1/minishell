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

void	process_command(t_cmd *cmd, int *input_fd, int fd[2])
{
	int (tmpout), (tmpint), (fdd);
	tmpout = 0;
	tmpint = 0;
	fdd = 0;
	if (is_builtin(cmd->cmd) && (check_stdout(cmd->files) \
			|| check_stdin(cmd->files)))
	{
		if (stdin_stdout(cmd, &tmpout, &tmpint))
		{
			fdd = start_std(cmd);
			if (fdd == -1)
				printf("%s: No such file or directory\n", cmd->files->file);
			else
				run_builtin(cmd);
		}
		if (cmd->files != NULL)
			restore_fd(tmpout, tmpint);
	}
	if (!is_builtin(cmd->cmd))
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
