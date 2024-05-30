/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:29:07 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/28 09:52:04 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_line_to_buffer(char *buffer, char *line)
{
	char	*tmp;
	char	*old_buffer;

	tmp = ft_strjoin3(line, "\n");
	if (buffer)
	{
		old_buffer = buffer;
		buffer = ft_strjoin3(old_buffer, tmp);
		free(old_buffer);
	}
	else
		buffer = ft_strdup(tmp);
	free(tmp);
	return (buffer);
}

char	*read_heredoc_input(char *limiter, int quoted)
{
	char	*buffer;
	char	*line;

	buffer = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || !ft_strcmp(limiter, line))
		{
			free(line);
			break ;
		}
		if (!quoted)
			line = herdoc_expander(line);
		buffer = append_line_to_buffer(buffer, line);
		free(line);
	}
	return (buffer);
}

void	handle_heredoc_file(t_files_redirections *files)
{
	int		fd;
	char	*buffer;

	fd = open(files->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
		exit(EXIT_FAILURE);
	buffer = read_heredoc_input(files->limiter, files->qouted);
	write(fd, buffer, ft_strlen(buffer));
	free(buffer);
	close(fd);
}

void	process_cmd_heredoc(t_cmd *cmd)
{
	t_files_redirections	*files;

	files = cmd->files;
	while (files)
	{
		if (files->type == HEREDOC)
		{
			handle_heredoc_file(files);
		}
		files = files->next;
	}
}

void	ft_herdoc(t_cmd *cmd)
{
	while (cmd)
	{
		process_cmd_heredoc(cmd);
		cmd = cmd->next;
	}
	exit(0);
}
