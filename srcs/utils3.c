#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;
extern int		g_sepia;

int		ft_create_trgb(int t, int r, int g, int b)
{
	if (g_sepia)
	{
		r = (r * 0.393) + (g * 0.769) + (b * 0.189);
		g = (r * 0.349) + (g * 0.686) + (b * 0.168);
		b = (r * 0.272) + (g * 0.534) + (b * 0.131);
	}
	r = fmin(255, fmax(0, r));
	g = fmin(255, fmax(0, g));
	b = fmin(255, fmax(0, b));
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_putpixel(t_mlxdata *data, int x, int y, t_color color)
{
	char	*dst;

	x = g_width / 2 + x;
	y = g_height / 2 - y - 1;
	dst = data->addr + (y * data->line_len + x * (data->bbp / 8));
	*(unsigned int*)dst = ft_create_trgb(255,
		(int)color.r, (int)color.g, (int)color.b);
}

t_color	ft_color_multiply(double a, t_color color)
{
	t_color	ret;

	ret.r = color.r * a;
	ret.g = color.g * a;
	ret.b = color.b * a;
	return (ret);
}

int		ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
		c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int		ft_atoi(char *str)
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
