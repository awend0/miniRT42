/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 02:12:06 by hasv              #+#    #+#             */
/*   Updated: 2021/02/28 08:37:49 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern double	g_width;
extern double	g_height;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_point	ft_vec_s(t_point a, t_point b)
{
	t_point	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

double	ft_vec_dot(t_point a, t_point b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

double	ft_vec_length(t_point a)
{
	return (sqrtf(ft_vec_dot(a, a)));
}

t_point	ft_vec_add(t_point a, t_point b)
{
	t_point ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_color	ft_color_add(t_color a, t_color b)
{
	t_color	ret;

	ret.r = a.r + b.r;
	ret.g = a.g + b.g;
	ret.b = a.b + b.b;
	return (ret);
}
