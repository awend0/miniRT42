/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:37:59 by hasv              #+#    #+#             */
/*   Updated: 2021/03/06 11:53:08 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_parsed_data	*ft_init_pd(void)
{
	t_parsed_data	*ret;

	ret = ft_malloc_save(sizeof(t_parsed_data));
	ret->cameras = 0;
	ret->lights = 0;
	ret->objects = 0;
	return (ret);
}

double			ft_stof(char *line)
{
	char	**temp;

	temp = ft_split(line, '.');
	if (!temp[1])
		return ((double)(ft_atoi(temp[0])));
	return ((double)ft_atoi(temp[0])
		+ ((double)ft_atoi(temp[1])
		/ pow(10, ft_strlen(temp[1]))));
}

t_color			ft_stoc(char *line)
{
	char	**temp;

	temp = ft_split(line, ',');
	return ((t_color){ft_stof(temp[0]), ft_stof(temp[1]), ft_stof(temp[2])});
}

t_point			ft_stop(char *line)
{
	char	**temp;

	temp = ft_split(line, ',');
	return ((t_point){ft_stof(temp[0]), ft_stof(temp[1]), ft_stof(temp[2])});
}

t_parsed_data	*ft_parse_processor(char *line, t_parsed_data *data)
{
	if (line[0] == 'R')
		ft_parse_res(line);
	if (line[0] == 'A')
		data->lights = ft_ladd(data->lights, ft_lnew(ft_parse_amb(line)));
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
	if (line[0] == 'c' && line[1] == 'o' && line[2] == ' ')
		data->objects = ft_ladd(data->objects, ft_lnew(ft_parse_cone(line)));
	if (line[0] == 's' && line[1] == 'q' && line[2] == ' ')
		data->objects = ft_ladd(data->objects, ft_lnew(ft_parse_square(line)));
	if (line[0] == 'c' && line[1] == 'u' && line[2] == ' ')
		data->objects = ft_ladd(data->objects, ft_parse_cube(line));
	return (data);
}
