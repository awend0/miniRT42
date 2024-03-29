#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_list	*ft_lnew(void *content)
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

t_list	*ft_ladd(t_list *lst, t_list *new)
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
