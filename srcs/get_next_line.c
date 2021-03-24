#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

int		ft_appendremainder(char **remainder, char *buf)
{
	char	*ptr;

	ptr = ft_strnew(ft_strlen(*remainder) + BUFFER_SIZE);
	ft_memcpy(ptr, *remainder, ft_strlen(*remainder));
	ft_memcpy(ptr + ft_strlen(*remainder), buf, ft_strlen(buf));
	*remainder = ptr;
	return (0);
}

int		ft_appendline(char **line, char **remainder)
{
	char	*new;
	char	*tmp;

	tmp = ft_strchr(*remainder, '\n');
	*line = ft_strnew(tmp - *remainder);
	new = ft_strnew(ft_strlen(*remainder));
	ft_memcpy(*line, *remainder, (tmp - *remainder));
	*tmp = 0;
	tmp++;
	ft_memcpy(new, tmp, ft_strlen(tmp));
	*remainder = new;
	return (0);
}

int		ft_appendline2(char **line, char **remainder)
{
	*line = ft_strnew(ft_strlen(*remainder));
	ft_memcpy(*line, *remainder, ft_strlen(*remainder));
	*remainder = 0;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*remainder;
	char		*buf;
	int			readret;

	if (!remainder)
		remainder = ft_strnew(0);
	buf = ft_strnew(BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, NULL, 0)) < 0
		|| !remainder || !buf || !line)
		return (-1);
	while ((readret = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		buf[readret] = 0;
		ft_appendremainder(&remainder, buf);
		if (ft_strchr(remainder, '\n'))
			return ((ft_appendline(line, &remainder) == -1) ? -1 : 1);
		if (readret < BUFFER_SIZE)
			return ((ft_appendline2(line, &remainder) == -1) ? -1 : 0);
	}
	return (-1);
}
