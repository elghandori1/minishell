/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lissam <lissam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:36:31 by lissam            #+#    #+#             */
/*   Updated: 2024/05/26 17:10:25 by lissam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_prompt_nodes	*lst_new2(char *str, t_types t)
{
	t_prompt_nodes	*new;

	new = (t_prompt_nodes *)malloc(sizeof(t_prompt_nodes));
	if (!new)
		return (NULL);
	new->string = str;
	new->type = t;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back2(t_prompt_nodes **lst, t_prompt_nodes *new)
{
	t_prompt_nodes	*last;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		last = *lst;
		while (last->next)
		{
			last = last->next;
		}
		last->next = new;
	}
}

void	skip_spaces(char *prompt, int *i, t_prompt_nodes **prompt_nodes)
{
	int		j;
	char	*temp;
	char	*str;

	j = 0;
	str = NULL;
	while ((prompt[*i] >= 9 && prompt[*i] <= 13) || prompt[*i] == ' ')
	{
		*i = *i + 1;
		j++;
	}
	if (j > 0)
	{
		temp = (char *)malloc(2 * sizeof(char));
		temp[0] = ' ';
		temp[1] = '\0';
		str = ft_strjoin2(str, temp);
		free(temp);
		add_to_prompt_nodes(str, &(*prompt_nodes), WHITE_SPACE);
	}
}

void	add_to_prompt_nodes(char *str, t_prompt_nodes **prompt_nodes,
		t_types type)
{
	t_prompt_nodes	*tmp_node;

	tmp_node = lst_new2(str, type);
	ft_lstadd_back2(&(*prompt_nodes), tmp_node);
}

void	free_prompt_nodes(t_prompt_nodes *node)
{
	t_prompt_nodes	*tmp;

	if (node)
	{
		while (node != NULL)
		{
			tmp = node->next;
			free(node->string);
			free(node);
			node = tmp;
		}
		node = NULL;
	}
}
