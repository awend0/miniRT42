/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:18:53 by hasv              #+#    #+#             */
/*   Updated: 2021/03/03 16:10:53 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern double	g_width;
extern double	g_height;
extern t_color	g_background_color;
extern t_list	*g_memory;

double			ft_stof(char *line)
{
	char	**temp;

	temp = ft_split(line, '.');
	if (!temp[1])
		return ((double)(ft_atoi(temp[0])));
	return ((double)ft_atoi(temp[0]) + ((double)ft_atoi(temp[1]) / pow(10, ft_strlen(temp[1]))));
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

t_light			*ft_parse_pnt(char *line)
{
	char	**words;
	t_light	*ret;

	ret = ft_malloc_save(sizeof(t_light));
	words = ft_split(line, ' ');
	ret->e_type = POINT;
	ret->position = ft_stop(words[1]);
	ret->intensity = ft_stof(words[2]);
	ret->color = ft_stoc(words[3]);
	return (ret);
}

t_light			*ft_parse_amb(char *line)
{
	char	**words;
	t_light	*ret;

	ret = ft_malloc_save(sizeof(t_light));
	words = ft_split(line, ' ');
	ret->e_type = AMBIENT;
	ret->intensity = ft_stof(words[1]);
	ret->color = ft_stoc(words[2]);
	return (ret);
}

void			ft_parse_res(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	g_width = 0;
	g_height = 0;
	g_width = (double)ft_atoi(words[1]);
	g_height = (double)ft_atoi(words[2]);
}

double			**ft_rotation_matrix(t_point A)
{
	double	**ret;
	t_point B;
	t_point C;

	ret = ft_malloc_save(3 * sizeof(double));
	ret[0] = ft_malloc_save(3 * sizeof(double));
	ret[1] = ft_malloc_save(3 * sizeof(double));
	ret[2] = ft_malloc_save(3 * sizeof(double));
	B = (t_point){0.0, 0.0, 1.0};
	C = ft_vec_cross(A, B);
	B = ft_vec_cross(C, A);
	ret[0][0] = B.x;
	ret[0][1] = C.x;
	ret[0][1] = C.y;
	ret[1][0] = B.y;
	ret[1][1] = C.y;
	ret[1][2] = A.y;
	ret[2][0] = B.z;
	ret[2][1] = C.z;
	ret[2][2] = A.z;
	return (ret); 	
}

t_camera		ft_parse_camera(char *line)
{
	char	**words;
	t_camera ret;

	words = ft_split(line, ' ');
	ret.pos = ft_stop(words[1]);
	ret.rotation = ft_vec_norm(ft_stop(words[2]));
	ret.fov = ft_stof(words[3]);
	ret.viewport.width = 2.0 * tan((ret.fov / 2.0) * (M_PI / 180.0));
	ret.viewport.height = ret.viewport.width / (g_width / g_height);
	ret.viewport.d = 1.0;
	return (ret);
}

t_object		*ft_parse_sphere(char *line)
{
	char			**words;
	t_object		*ret;
	t_sphereParams	params;

	words = ft_split(line, ' ');
	params.center = ft_stop(words[1]);
	params.radius = ft_stof(words[2]);
	params.color = ft_stoc(words[3]);
	params.reflection = 0.5;
	params.spec = 500;
	if (words[4])
		params.reflection = ft_stof(words[4]);
	if (words[5])
		params.spec = ft_stof(words[5]);
	ret = ft_create_sphere(params);
	return (ret);
}

t_list	*ft_cylinder_caps(t_object *obj, t_cylinderParams params)
{
	t_list	*ret;
	t_object		*top_cap;
	t_object		*bottom_cap;

	top_cap = ft_create_disc((t_discParams){params.p, ft_vec_multiply(-1, params.orient),
		params.color, params.diam / 2.0, params.reflection, params.spec});
	bottom_cap = ft_create_disc((t_discParams){ft_vec_add(params.p, ft_vec_multiply(params.height, params.orient)), params.orient,
		params.color, params.diam / 2.0, params.reflection, params.spec});
	ret = ft_lstnew(obj);
	ret->next = ft_lstnew(top_cap);
	((t_list*)ret->next)->next = ft_lstnew(bottom_cap);
	return (ret);
}

t_list	*ft_parse_cylinder(char *line, int caps)
{
	char				**words;
	t_object			*ret;
	t_cylinderParams	params;

	words = ft_split(line, ' ');
	params.p = ft_stop(words[1]);
	params.orient = ft_vec_norm(ft_stop(words[2]));
	params.color = ft_stoc(words[3]);
	params.diam = ft_stof(words[4]);
	params.height = ft_stof(words[5]);
	params.reflection = 0.5;
	params.spec = 500;
	if (words[6])
		params.reflection = ft_stof(words[6]);
	if (words[7])
		params.spec = ft_stof(words[7]);
	ret = ft_create_cylinder(params);
	if (caps)
		return (ft_cylinder_caps(ret, params));
	return (ft_lstnew(ret));
}

t_object		*ft_parse_cone(char *line)
{
	char			**words;
	t_object		*ret;
	t_coneParams	params;

	words = ft_split(line, ' ');
	params.p = ft_stop(words[1]);
	params.orient = ft_vec_norm(ft_stop(words[2]));
	params.minm = ft_stof(words[3]);
	params.maxm = ft_stof(words[4]);
	params.k = ft_stof(words[5]);
	params.color = ft_stoc(words[6]);
	params.reflection = 0.5;
	params.spec = 500;
	if (words[7])
		params.reflection = ft_stof(words[7]);
	if (words[8])
		params.spec = ft_stof(words[8]);
	ret = ft_create_cone(params);
	return (ret);
}

t_object		*ft_parse_triangle(char *line)
{
	char				**words;
	t_object			*ret;
	t_triangleParams	params;

	words = ft_split(line, ' ');
	params.a = ft_stop(words[1]);
	params.b = ft_stop(words[2]);
	params.c = ft_stop(words[3]);
	params.color = ft_stoc(words[4]);
	params.reflection = 0.5;
	params.spec = 500;
	if (words[5])
		params.reflection = ft_stof(words[5]);
	if (words[6])
		params.spec = ft_stof(words[6]);
	ret = ft_create_triangle(params);
	return (ret);
}

t_object		*ft_parse_plane(char *line)
{
	char			**words;
	t_object		*ret;
	t_planeParams	params;

	words = ft_split(line, ' ');
	params.p = ft_stop(words[1]);
	params.norm = ft_stop(words[2]);
	params.color = ft_stoc(words[3]);
	params.reflection = 0.5;
	params.spec = 500;
	if (words[4])
		params.reflection = ft_stof(words[4]);
	if (words[5])
		params.spec = ft_stof(words[5]);
	ret = ft_create_plane(params);
	return (ret);
}

t_object		*ft_parse_disc(char *line)
{
	char			**words;
	t_object		*ret;
	t_discParams	params;

	words = ft_split(line, ' ');
	params.p = ft_stop(words[1]);
	params.norm = ft_stop(words[2]);
	params.r = ft_stof(words[3]);
	params.color = ft_stoc(words[4]);
	params.reflection = 0.5;
	params.spec = 500;
	if (words[5])
		params.reflection = ft_stof(words[5]);
	if (words[6])
		params.spec = ft_stof(words[6]);
	ret = ft_create_disc(params);
	return (ret);
}

t_parsed_data	*ft_parse_processor(char *line, t_parsed_data *data)
{
	if (line[0] == 'R')
		ft_parse_res(line);
	if (line[0] == 'A')
		data->lights = ft_lstadd_back(data->lights, ft_lstnew(ft_parse_amb(line)));
	if (line[0] == 'c' && line[1] == ' ')
		data->camera = ft_parse_camera(line);
	if (line[0] == 'l' && line[1] == ' ')
		data->lights = ft_lstadd_back(data->lights, ft_lstnew(ft_parse_pnt(line)));
	if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		data->objects = ft_lstadd_back(data->objects, ft_lstnew(ft_parse_sphere(line)));
	if (line[0] == 't' && line[1] == 'r' && line[2] == ' ')
		data->objects = ft_lstadd_back(data->objects, ft_lstnew(ft_parse_triangle(line)));
	if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		data->objects = ft_lstadd_back(data->objects, ft_lstnew(ft_parse_plane(line)));
	if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		data->objects = ft_lstadd_back(data->objects, ft_parse_cylinder(line, 0));
	if (line[0] == 'C' && line[1] == 'Y' && line[2] == ' ')
		data->objects = ft_lstadd_back(data->objects, ft_parse_cylinder(line, 1));
	if (line[0] == 'd' && line[1] == 's' && line[2] == ' ')
		data->objects = ft_lstadd_back(data->objects, ft_lstnew(ft_parse_disc(line)));
	if (line[0] == 'c' && line[1] == 'o' && line[2] == ' ')
		data->objects = ft_lstadd_back(data->objects, ft_lstnew(ft_parse_cone(line)));
	return (data);
}

t_parsed_data	*ft_parser(int argc, char *argv[])
{
	t_parsed_data	*ret;
	int				fd;
	char			*line;
	int				i;

	ret = ft_malloc_save(sizeof(t_parsed_data));
	ret->lights = 0;
	ret->objects = 0;
	if (argc >= 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (1)
		{
			i = get_next_line(fd, &line);
			if (i == 1)
				ret = ft_parse_processor(line, ret);
			else if (i == -1)
				return (0);
			else if (i == 0)
			{
				ret = ft_parse_processor(line, ret);
				break;
			}
		}
		close(fd);
	}
	return (ret);
}
