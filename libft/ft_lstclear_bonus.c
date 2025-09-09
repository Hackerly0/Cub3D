/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:56:19 by salshaha          #+#    #+#             */
/*   Updated: 2024/09/09 17:26:09 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*s;

	node = *lst;
	if (lst == NULL)
		return ;
	while (node != NULL)
	{
		s = node->next;
		del(node->content);
		free(node);
		node = s;
	}
	*lst = NULL;
}
