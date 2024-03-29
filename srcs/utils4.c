#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_point		ft_reflect_ray(t_point r, t_point n)
{
	return (ft_vec_s(ft_vec_mul(2.0 * ft_vec_dot(r, n), n), r));
}

int			ft_isdigit(char *str)
{
	char	*ptr;

	ptr = str;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	while (*ptr)
	{
		if (!(*ptr >= '0' && *ptr <= '9'))
			return (0);
		ptr++;
	}
	return (1);
}

int			ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (!*s1)
			return (0);
		s1++;
		s2++;
	}
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

int			ft_open_map(char *filename)
{
	int	ret;

	if (filename[ft_strlen(filename) - 2] != 'r' &&
		filename[ft_strlen(filename) - 1] != 't')
		ft_exit(0, "Configuration file must be in .rt extension.");
	ret = open(filename, O_RDONLY);
	return (ret);
}

t_color		ft_color_average(t_color a, t_color b)
{
	t_color		ret;

	ret.r = a.r * b.r / 255;
	ret.g = a.g * b.g / 255;
	ret.b = a.b * b.b / 255;
	return (ret);
}
