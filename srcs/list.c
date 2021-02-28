/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 00:22:08 by hasv              #+#    #+#             */
/*   Updated: 2021/02/28 03:41:20 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*cur;

	cur = malloc(sizeof(t_list));
	if (!cur)
		return (0);
	if (!content)
		cur->node = 0;
	else
		cur->node = content;
	cur->next = 0;
	return (cur);
}

t_list	*ft_lstadd_back(t_list *lst, t_list *new)
{
	t_list	*ret;
	t_list	*cur;

	if (!lst)
	{
		lst = new;
		return (lst);
	}
	cur = lst;
	ret = lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (ret);
}
