/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 12:17:18 by hasv              #+#    #+#             */
/*   Updated: 2021/03/16 03:29:32 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

double		ft_max3(double a, double b, double c)
{
	if (a >= b && a >= c)
		return (a);
	if (b >= a && b >= c)
		return (b);
	return (c);
}

t_color		ft_color_mix_light(t_color a, t_color b)
{
	t_color		ret;

	ret.r = a.r * b.r / 255;
	ret.g = a.g * b.g / 255;
	ret.b = a.b * b.b / 255;
	return (ret);
}

t_color		ft_color_add_light(t_color a, t_color b)
{
	t_color		ret;

	ret.r = fmax(a.r, b.r);
	ret.g = fmax(a.g, b.g);
	ret.b = fmax(a.b, b.b);
	return (ret);
}
