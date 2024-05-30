/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:31:09 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/27 21:53:06 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute2(t_cmd *ex, int tmpout, int tmpint, int fd)
{
	if (stdin_stdout(ex, &tmpout, &tmpint))
	{
		fd = start_std(ex);
		if (fd == -1)
			printf("No such file or directory\n");
	}
	if (ex->cmd)
	{
		if (is_builtin(ex->cmd))
			run_builtin(ex);
		else
			run_cmd(ex);
	}
	if (ex->files != NULL)
		restore_fd(tmpout, tmpint);
}

void	ft_execute(t_cmd *ex)
{
	int (tmpout), (tmpint), (fd);
	tmpout = 0;
	tmpint = 0;
	fd = 0;
	if ((ex->files && !ex->files->file) || ((ex->files) && ambiguous(ex) && \
		(ex->files->qouted == 0)))
	{
		printf("minishell: ambiguous redirect\n");
		return ;
	}
	else
		ft_execute2(ex, tmpout, tmpint, fd);
}

void	start_execution(t_cmd *prmpt)
{
	t_cmd	*tmprmpt;

	int (hereDocProcess), (herdoc_count);
	tmprmpt = prmpt;
	herdoc_count = count_heredoc(tmprmpt);
	if (herdoc_count > 16)
	{
		printf("Maximum here-document count exceeded\n");
		cleanup_g_lobal_env();
		exit(2);
	}
	hereDocProcess = fork();
	if (hereDocProcess == -1)
		perror("Fork");
	if (hereDocProcess == 0)
	{
		signal(SIGINT, handler_hd);
		ft_herdoc(prmpt);
	}
	else
		waitpid(hereDocProcess, NULL, 0);
	if (check_pipe(prmpt))
		ft_pipe(prmpt);
	else
		ft_execute(prmpt);
}
