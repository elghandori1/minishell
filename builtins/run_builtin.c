/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:48:27 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/22 10:39:06 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

void	run_builtin(t_cmd *built)
{
	t_cmd	*bui;

	bui = built;
	if (ft_strcmp(bui->cmd, "echo") == 0)
		ft_echo(bui);
	if (ft_strcmp(bui->cmd, "env") == 0)
		ft_env(g_lobal_env);
	if (ft_strcmp(bui->cmd, "pwd") == 0)
		ft_pwd();
	if ((ft_strcmp(bui->cmd, "cd") == 0))
		ft_cd(bui, g_lobal_env);
	if (ft_strcmp(bui->cmd, "exit") == 0)
		ft_exit(bui);
	if (ft_strcmp(bui->cmd, "export") == 0)
		ft_export(bui);
	if (ft_strcmp(bui->cmd, "unset") == 0)
		ft_unset(bui);
}
