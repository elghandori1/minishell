/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:15:41 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/28 09:56:10 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_io_redirect(t_cmd *cmd, int input_fd, int output_fd)
{
	if (check_stdin(cmd->files))
		run_stdin(cmd->files);
	else if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (check_stdout(cmd->files))
		run_stdout(cmd->files);
	else if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
}

void	exec_command(char *path, char **args, char **env_array, int *fd)
{
	if (fd != NULL)
		close(fd[0]);
	if (execve(path, args, env_array) == -1)
	{
		ft_free_all(env_array);
		perror("execve");
		exit(127);
	}
}

void	child_process(t_cmd *cmd, int input_fd, int output_fd, int *fd)
{
	char	**env_array;
	char	*path;

	env_array = env_to_array(g_lobal_env);
	path = get_path(cmd->args[0], env_array);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	handle_io_redirect(cmd, input_fd, output_fd);
	exec_command(path, cmd->args, env_array, fd);
}

void	run_pipeline(t_cmd *cmd, int input_fd, int output_fd, int *fd)
{
	pid_t	pid;
	char	**env_array;
	char	*path;
	char	**args;

	args = cmd->args;
	env_array = env_to_array(g_lobal_env);
	path = get_path(args[0], env_array);
	free_rcrs(path, env_array);
	if (path != NULL)
	{
		pid = fork();
		if (pid == 0)
			child_process(cmd, input_fd, output_fd, fd);
		else
		{
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			if (output_fd != STDOUT_FILENO)
				close(output_fd);
		}
	}
	else
		cmd_not_found(args[0]);
}

void	ft_pipe(t_cmd *cmds)
{
	t_cmd	*cmd;
	int		input_fd;
	int		fd[2];

	cmd = cmds;
	input_fd = STDIN_FILENO;
	if (cmd->cmd)
	{
		while (cmd->next != NULL)
		{
			if (pipe(fd) == -1)
				handle_pipe_error();
			process_command(cmd, &input_fd, fd);
			cmd = cmd->next;
		}
		finalize_pipeline(cmd, input_fd);
	}
}
