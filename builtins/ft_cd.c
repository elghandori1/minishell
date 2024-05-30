/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:47:53 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/26 20:34:43 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_and_free_pwd(t_env *my_env, char *oldpwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	update_env_value(my_env, "PWD", pwd);
	update_env_value(my_env, "OLDPWD", oldpwd);
	free(pwd);
}

char	*get_oldpwd_value(t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	handle_home_path(t_cmd *path, t_env *my_env, char *oldpwd)
{
	char	*home_dir;

	if ((path->args[0] != NULL && path->args[1] == NULL)
		|| (path->args[1] != NULL && ft_strcmp(path->args[1], "~") == 0))
	{
		if ((path->args[0] != NULL) && !(seaech_home(my_env)))
			printf("cd: HOME not set\n");
		else
		{
			home_dir = getenv("HOME");
			chdir(home_dir);
		}
	}
	else if (path->args[1] != NULL && chdir(path->args[1]) != 0)
	{
		printf("cd: %s: No such file or directory\n", path->args[1]);
		set_status(1);
	}
	else
		update_and_free_pwd(my_env, oldpwd);
}

void	handle_path(t_cmd *path, t_env *my_env, char *oldpwd)
{
	char	*oldpwd_value;

	if (path->args[1] != NULL && ft_strcmp(path->args[1], "-") == 0)
	{
		oldpwd_value = get_oldpwd_value(my_env);
		if (oldpwd_value != NULL)
		{
			if (*oldpwd_value == '\0')
			{
				printf("minishell: cd: OLDPWD not set\n");
				set_status(1);
				return ;
			}
			if (chdir(oldpwd_value) == 0)
				update_and_free_pwd(my_env, oldpwd);
		}
	}
	else
		handle_home_path(path, my_env, oldpwd);
}

void	ft_cd(t_cmd *path, t_env *my_env)
{
	char	oldpwd[1024];

	getcwd(oldpwd, sizeof(oldpwd));
	if (path != NULL && path->args != NULL)
	{
		handle_path(path, my_env, oldpwd);
	}
}
