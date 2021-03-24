#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;
extern int		g_sepia;

t_parsed_data	*ft_parse_processor2(char *line, t_parsed_data *data)
{
	if (line[0] == 's' && line[1] == 'q' && line[2] == ' ')
		data->objects = ft_ladd(data->objects, ft_lnew(ft_parse_square(line)));
	if (line[0] == 'c' && line[1] == 'u' && line[2] == ' ')
		data->objects = ft_ladd(data->objects, ft_parse_cube(line));
	if (line[0] == 'p' && line[1] == 'y' && line[2] == ' ')
		data->objects = ft_ladd(data->objects, ft_parse_pyramid(line));
	return (data);
}

t_parsed_data	*ft_parse_processor(char *line, t_parsed_data *data)
{
	if (line[0] == 'R')
		ft_parse_res(line);
	if (line[0] == 'A')
		data->lights = ft_ladd(data->lights, ft_lnew(ft_parse_amb(line)));
	if (line[0] == 'S')
		g_sepia = 1;
	if (line[0] == 'c' && line[1] == ' ')
		data->cameras = ft_ladd(data->cameras, ft_lnew(ft_parse_camera(line)));
	if (line[0] == 'l' && line[1] == ' ')
		data->lights = ft_ladd(data->lights, ft_lnew(ft_parse_pnt(line)));
	if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		data->objects = ft_ladd(data->objects, ft_lnew(ft_parse_sphere(line)));
	if (line[0] == 't' && line[1] == 'r' && line[2] == ' ')
		data->objects = ft_ladd(data->objects, ft_lnew(ft_parse_tr(line)));
	if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		data->objects = ft_ladd(data->objects, ft_lnew(ft_parse_plane(line)));
	if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		data->objects = ft_ladd(data->objects, ft_parse_cylinder(line));
	if (line[0] == 'd' && line[1] == 's' && line[2] == ' ')
		data->objects = ft_ladd(data->objects, ft_lnew(ft_parse_disc(line)));
	return (ft_parse_processor2(line, data));
}
