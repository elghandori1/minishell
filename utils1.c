/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:39:56 by lissam            #+#    #+#             */
/*   Updated: 2024/05/26 18:42:18 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_files(t_files_redirections *files)
{
	t_files_redirections	*files_redirections;

	files_redirections = NULL;
	while (files)
	{
		files_redirections = files->next;
		if (files->file)
			free(files->file);
		if (files->limiter)
			free(files->limiter);
		free(files);
		files = files_redirections;
	}
	files = NULL;
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i])
			free(args[i]);
		i++;
	}
}
