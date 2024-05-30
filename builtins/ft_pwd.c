/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:48:18 by moel-gha          #+#    #+#             */
/*   Updated: 2024/05/26 20:34:10 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	t_env	*erp;
	char	cwd[1024];

	erp = g_lobal_env;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s", cwd);
	else
	{
		while (erp != NULL)
		{
			if (ft_strcmp(erp->key, "PWD") == 0)
			{
				printf("%s\n", erp->value);
				return ;
			}
			erp = erp->next;
		}
	}
	printf("\n");
}

int	seaech_home(t_env *my_env)
{
	while (my_env != NULL)
	{
		if (ft_strcmp(my_env->key, "HOME") == 0)
			return (1);
		my_env = my_env->next;
	}
	return (0);
}
