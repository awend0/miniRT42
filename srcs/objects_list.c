/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 00:23:59 by hasv              #+#    #+#             */
/*   Updated: 2021/02/05 08:50:53 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_objectsList	*ft_olstnew(t_object *content)
{
	t_objectsList	*node;

	node = malloc(sizeof(t_objectsList));
	if (!content)
		node->obj = 0;
	else
		node->obj = content;
	node->next = 0;
	return (node);
}

t_objectsList	*ft_olstadd_back(t_objectsList *lst, t_objectsList *new)
{
	t_objectsList	*ret;
	t_objectsList	*cur;

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
