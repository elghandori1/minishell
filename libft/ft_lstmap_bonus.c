/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:21:44 by moel-gha          #+#    #+#             */
/*   Updated: 2023/11/27 10:03:31 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head_elem;
	t_list	*new_elem;

	head_elem = NULL;
	if (!lst)
		return (NULL);
	if (f && del)
	{
		while (lst)
		{
			new_elem = ft_lstnew(f(lst->content));
			if (!new_elem)
			{
				ft_lstclear(&head_elem, del);
				return (NULL);
			}
			ft_lstadd_back(&head_elem, new_elem);
			lst = lst->next;
		}
	}
	return (head_elem);
}
