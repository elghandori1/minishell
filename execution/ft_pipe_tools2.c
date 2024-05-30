/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:25:43 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/26 10:16:42 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_not_found(char *command)
{
	printf("%s:command not found\n", command);
	set_status(127);
}

void	free_rcrs(char *path, char **env_array)
{
	if (path)
	{
		free(path);
		path = NULL;
	}
	ft_free_all(env_array);
}

void	set_status(int status)
{
	t_env	*env;

	env = g_lobal_env;
	env->status = status;
}

int	check_builts(t_cmd *cmd)
{
	if ((ft_strcmp(cmd->cmd, "export") == 0) || (ft_strcmp(cmd->cmd, "cd") == 0)
		|| (ft_strcmp(cmd->cmd, "unset") == 0) || (ft_strcmp(cmd->cmd,
				"exit") == 0))
		return (1);
	return (0);
}
