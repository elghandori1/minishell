/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_run_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:19:31 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/27 21:39:52 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_all(char **f)
{
	size_t	i;

	i = 0;
	while (f && f[i])
	{
		free(f[i]);
		f[i] = NULL;
		i++;
	}
	free(f);
	f = NULL;
}

char	*ft_freepath(char *pat)
{
	char	*path;

	path = pat;
	if (path)
		return (path);
	else
	{
		free(path);
		path = NULL;
		return (path);
	}
}

char	*get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_exec_path(char *path, char *cmd)
{
	char	*path_part;
	char	*exec;

	if (!path || !cmd)
		return (NULL);
	path_part = ft_strjoin(path, "/");
	exec = ft_strjoin(path_part, cmd);
	free(path_part);
	path_part = NULL;
	if (access(exec, X_OK) == 0)
		return (exec);
	else
	{
		free(exec);
		exec = NULL;
		return (NULL);
	}
}

char	*get_path(char *cmd, char **env)
{
	char	*path_env;
	char	**paths;
	char	*path;
	int		i;
	char	*cm;

	path_env = get_env("PATH", env);
	cm = ft_strdup(cmd);
	if (ft_strchr(cm, '/'))
		return (cm);
	free(cm);
	if (path_env == NULL)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = -1;
	path = NULL;
	while (paths[++i])
	{
		path = get_exec_path(paths[i], cmd);
		if (path != NULL)
			break ;
	}
	ft_free_all(paths);
	path = ft_freepath(path);
	return (path);
}
