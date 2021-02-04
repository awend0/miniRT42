/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 02:12:06 by hasv              #+#    #+#             */
/*   Updated: 2021/02/04 03:25:04 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern float g_width;
extern float g_height;
extern t_color g_backgroundColor;

t_point	ft_vecSubtract(t_point O, t_point D)
{
	t_point	ret;

	ret.x = O.x - D.x;
	ret.y = O.y - D.y;
	ret.z = O.z - D.z;
	return (ret);
}

float	ft_vecDot(t_point a, t_point b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

float	ft_vecLength(t_point a)
{
	return (sqrtf(ft_vecDot(a, a)));
}

t_point ft_vecAdd(t_point a, t_point b)
{
	t_point ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_point ft_vecMultiply(float k, t_point a)
{
	t_point ret;

	ret.x = a.x * k;
	ret.y = a.y * k;
	ret.z = a.z * k;
	return (ret);
}

int				ft_createTrgb(int t, int r, int g, int b)
{
	r = fmin(255, fmax(0, r));
	g = fmin(255, fmax(0, g));
	b = fmin(255, fmax(0, b));
	return(t << 24 | r << 16 | g << 8 | b);
}

void			ft_putPixel(t_mlxdata *data, int x, int y, t_color color)
{
    char    *dst;

	x = g_width / 2 + x;
	y = g_height / 2 - y - 1;
    dst = data->addr + (y * data->lineLength + x * (data->bbp / 8));
    *(unsigned int*)dst = ft_createTrgb(255, (int)color.r, (int)color.g, (int)color.b);
}

t_color			ft_colorMultiply(float a, t_color color)
{
	t_color	ret;

	ret.r = color.r * a;
	ret.g = color.g * a;
	ret.b = color.b * a;
	return (ret);
}

t_color			ft_colorAdd(t_color a, t_color b)
{
	t_color	ret;

	ret.r = a.r + b.r;
	ret.g = a.g + b.g;
	ret.b = a.b + b.b;
	return (ret);
}

int		ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
		c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int			ft_atoi(char *str)
{
	long	res;
	int		negative;
	int		len;

	negative = 1;
	res = 0;
	len = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		res = res * 10 + (*str - '0');
		str++;
		len++;
		if (len > 10)
			return (negative == -1 ? 0 : -1);
	}
	return (res * negative);
}