#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char*)s;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_malloc_save(int size)
{
	void	*ret;
	t_list	*cur;
	t_list	*new;

	ret = malloc(size);
	if (!ret)
		ft_exit(0, "Malloc error o.o");
	ft_bzero(ret, size);
	new = malloc(sizeof(t_list));
	if (!new)
		ft_exit(0, "Malloc error o.o");
	new->node = ret;
	new->next = 0;
	if (!g_memory)
	{
		g_memory = malloc(sizeof(t_list));
		g_memory->node = malloc(1);
		g_memory->next = 0;
	}
	cur = g_memory;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (ret);
}

void	ft_free(void)
{
	t_list	*cur;
	t_list	*temp;

	cur = g_memory;
	while (cur)
	{
		temp = cur;
		cur = temp->next;
		free(temp->node);
		free(temp);
	}
}
