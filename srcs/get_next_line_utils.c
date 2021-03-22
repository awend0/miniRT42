/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymun <mraymun@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 21:28:39 by mraymun           #+#    #+#             */
/*   Updated: 2021/03/22 00:36:03 by mraymun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

char	*ft_strnew(int size)
{
	return ((char*)ft_memalloc(sizeof(char) * (size + 1)));
}

char	*ft_strchr(char *s, int c)
{
	while (*s && !(*s == c))
		s++;
	return ((*s == c) ? s : 0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*source;

	if (!dst)
		return (0);
	source = src;
	dest = dst;
	while (n--)
		*dest++ = *source++;
	return (dst);
}

void	*ft_memalloc(int size)
{
	void	*ptr;
	char	*tmp;

	ptr = ft_malloc_save(size);
	tmp = ptr;
	while (size--)
		*tmp++ = '\0';
	return (ptr);
}

int		ft_strlen(char *str)
{
	int		size;

	size = 0;
	while (*str)
	{
		size++;
		str++;
	}
	return (size);
}
