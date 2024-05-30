/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:29:47 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/26 20:00:54 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_shlvl(t_env *g_lobal_env)
{
	t_env	*exist_node;
	char	*cnv;
	char	*new_value;
	int		shlvl;

	exist_node = g_lobal_env;
	while (exist_node != NULL)
	{
		if (ft_strcmp(exist_node->key, "SHLVL") == 0)
		{
			shlvl = ft_atoi(exist_node->value);
			shlvl++;
			cnv = ft_itoa(shlvl);
			new_value = ft_strdup(cnv);
			free(cnv);
			if (new_value != NULL)
			{
				free(exist_node->value);
				exist_node->value = new_value;
			}
			break ;
		}
		exist_node = exist_node->next;
	}
}

void	setup_environment(t_cmd *cmd, char ***env_array, char **path)
{
	char	**local_env_array;
	char	*local_path;

	local_env_array = env_to_array(g_lobal_env);
	local_path = get_path(cmd->args[0], local_env_array);
	if ((ft_strcmp(cmd->args[0], "expr") == 0) && (g_lobal_env->status == 0))
		set_status(1);
	else
		set_status(0);
	*env_array = local_env_array;
	*path = local_path;
}

void	handle_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit:  (core dumped)\n");
		set_status(128 + WTERMSIG(status));
	}
	else if (WIFEXITED(status))
		set_status(WEXITSTATUS(status));
}

void	execute_command(t_cmd *cmd, char **env_array, char *path)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, handler);
	pid = fork();
	if (pid == -1)
		(perror("fork"), exit(1));
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (ft_strcmp(path, "./minishell") == 0)
		{
			(change_shlvl(g_lobal_env), ft_free_all(env_array));
			env_array = env_to_array(g_lobal_env);
		}
		if (execve(path, cmd->args, env_array) == -1)
			(ft_free_all(env_array), perror("execve"), exit(127));
		ft_free_all(env_array);
		exit(0);
	}
	else
		(waitpid(pid, &status, 0), handle_status(status));
}

void	run_cmd(t_cmd *cmd)
{
	char	**env_array;
	char	*path;

	setup_environment(cmd, &env_array, &path);
	if (path != NULL)
	{
		execute_command(cmd, env_array, path);
	}
	else
	{
		set_status(127);
		printf("minishell: %s: command not found\n", cmd->args[0]);
	}
	free(path);
	path = NULL;
	ft_free_all(env_array);
}
