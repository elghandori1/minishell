/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:42:44 by lissam            #+#    #+#             */
/*   Updated: 2024/05/28 10:18:23 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_lobal_env = NULL;

int	check_spaces(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp_cmds;

	while (cmds)
	{
		tmp_cmds = cmds->next;
		if (cmds->cmd)
		{
			free(cmds->cmd);
			cmds->cmd = NULL;
		}
		if (cmds->args)
			free_args(cmds->args);
		free(cmds->args);
		cmds->args = NULL;
		if (cmds->files)
			free_files(cmds->files);
		free(cmds);
		cmds = tmp_cmds;
	}
}

void	ft_minishell(void)
{
	char	*prompt;
	t_cmd	*cmds;

	while (1)
	{
		signal(SIGINT, handle_sigint);
		prompt = readline("minishell$ ");
		if (!prompt)
		{
			printf("exit\n");
			break ;
		}
		add_history(prompt);
		if (ft_strcmp(prompt, "\0") == 0 || check_spaces(prompt))
		{
			free(prompt);
			continue ;
		}
		cmds = lexer(prompt);
		if (cmds)
			start_execution(cmds);
		free_cmds(cmds);
		free(prompt);
	}
	cleanup_g_lobal_env();
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac > 1)
	{
		ft_putstr_fd("Invalid number of params\n", 2);
		return (1);
	}
	if (env[0] == NULL)
		g_lobal_env = behavior_env();
	else
		g_lobal_env = convert_env(env);
	signal(SIGQUIT, SIG_IGN);
	ft_minishell();
	return (0);
}
