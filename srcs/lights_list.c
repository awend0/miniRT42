/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 00:22:08 by hasv              #+#    #+#             */
/*   Updated: 2021/02/05 08:49:57 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_lightsList	*ft_lstnew(t_light *content)
{
	t_lightsList	*node;

	node = malloc(sizeof(t_lightsList));
	if (!node)
		return (0);
	if (!content)
		node->light = 0;
	else
		node->light = content;
	node->next = 0;
	return (node);
}

t_lightsList	*ft_lstadd_back(t_lightsList *lst, t_lightsList *new)
{
	t_lightsList	*ret;
	t_lightsList	*cur;

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
