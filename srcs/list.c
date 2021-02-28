/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 00:22:08 by hasv              #+#    #+#             */
/*   Updated: 2021/02/28 04:09:55 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern double	g_width;
extern double	g_height;
extern t_color	g_background_color;
extern t_list	*memory;

t_list	*ft_lstnew(void *content)
{
	t_list	*ret;

	ret = ft_malloc_save(sizeof(t_list));
	if (!ret)
		return (0);
	if (!content)
		ret->node = 0;
	else
		ret->node = content;
	ret->next = 0;
	return (ret);
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
