/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:26:56 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/28 10:02:20 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	restore_fd(int tmpout, int tmpint)
{
	if (tmpout != -1)
	{
		dup2(tmpout, STDOUT_FILENO);
		close(tmpout);
	}
	if (tmpint != -1)
	{
		dup2(tmpint, STDIN_FILENO);
		close(tmpint);
	}
}

int	handle_output_redirection(t_files_redirections *file)
{
	int	fd;

	if (file->type == REDIRECT_APPEND)
		fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

int	handle_input_redirection(t_files_redirections *file)
{
	int	fd;

	fd = open(file->file, O_RDONLY);
	if (fd == -1)
	{
		set_status(1);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	return (0);
}

int	start_std(t_cmd *srgs)
{
	t_files_redirections	*file;

	file = srgs->files;
	while (file)
	{
		if (file->type == REDIRECT_OUTPUT || file->type == REDIRECT_APPEND)
		{
			if (handle_output_redirection(file) == -1)
				return (-1);
		}
		else if (file->type == REDIRECT_INPUT || file->type == HEREDOC)
		{
			if (handle_input_redirection(file) == -1)
				return (-1);
		}
		file = file->next;
	}
	return (0);
}
