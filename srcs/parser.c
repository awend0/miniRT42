/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:18:53 by hasv              #+#    #+#             */
/*   Updated: 2021/02/05 07:50:26 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern float 	g_width;
extern float 	g_height;
extern t_color	g_backgroundColor;

float			ft_stof(char *line)
{
	char	**temp;

	temp = ft_split(line, '.');
	if (!temp[1])
		return ((float)(ft_atoi(temp[0])));
	return ((float)ft_atoi(temp[0]) + ((float)ft_atoi(temp[1]) / powf(10, ft_strlen(temp[1]))));
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

t_light			*ft_parsePoint(char *line)
{
	char	**words;
	t_light	*ret;

	ret = malloc(sizeof(t_light));
	words = ft_split(line, ' ');
	ret->e_type = POINT;
	ret->position = ft_stop(words[1]);
	ret->intensity = ft_stof(words[2]);
	ret->color = ft_stoc(words[3]);
	free(words);
	return (ret);
}

t_light			*ft_parseA(char *line)
{
	char	**words;
	t_light	*ret;

	ret = malloc(sizeof(t_light));
	words = ft_split(line, ' ');
	ret->e_type = AMBIENT;
	ret->intensity = ft_stof(words[1]);
	ret->color = ft_stoc(words[2]);
	return (ret);
}

void			ft_parseRes(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	g_width = 0;
	g_height = 0;
	g_width = (float)ft_atoi(words[1]);
	g_height = (float)ft_atoi(words[2]);
	free (words);
}

float			**ft_rotationMatrix(t_point A)
{
	float	**ret;
	t_point B;
	t_point C;

	ret = malloc(3 * sizeof(float));
	ret[0] = malloc(3 * sizeof(float));
	ret[1] = malloc(3 * sizeof(float));
	ret[2] = malloc(3 * sizeof(float));
	B = (t_point){0.0, 0.0, 1.0};
	C = ft_vecCross(A, B);
	B = ft_vecCross(C, A);
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
t_camera		ft_parseCam(char *line)
{
	char	**words;
	t_camera ret;

	words = ft_split(line, ' ');
	ret.pos = ft_stop(words[1]);
	ret.rotation = ft_rotationMatrix(ft_stop(words[2]));
	ret.fov = ft_stof(words[3]);
	ret.viewport = (t_viewport){1.0, 1.0, 1.0};
	free (words);
	return (ret);
}

t_object		*ft_parseSphere(char *line)
{
	char			**words;
	t_object		*ret;
	t_sphereParams	params;

	ret = malloc(sizeof(t_sphere));
	words = ft_split(line, ' ');
	params.center = ft_stop(words[1]);
	params.radius = ft_stof(words[2]);
	params.color = ft_stoc(words[3]);
	params.reflection = 0.5;
	params.spec = 500;
	if (words[4])
		params.reflection = ft_stof(words[4]);
	if (words[5])
		params.spec = (float)ft_atoi(words[5]);
	ret = ft_createSphere(params);
	free (words);
	return (ret);
}

t_object		*ft_parseTriangle(char *line)
{
	char				**words;
	t_object			*ret;
	t_triangleParams	params;

	ret = malloc(sizeof(t_triangle));
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
	ret = ft_createTriangle(params);
	free (words);
	return (ret);
}

t_parsedData	*ft_parseProcessor(char *line, t_parsedData *data)
{
	if (line[0] == 'R')
		ft_parseRes(line);
	if (line[0] == 'A')
		data->lights = ft_lstadd_back(data->lights, ft_lstnew(ft_parseA(line)));
	if (line[0] == 'c')
		data->camera = ft_parseCam(line);
	if (line[0] == 'l')
		data->lights = ft_lstadd_back(data->lights, ft_lstnew(ft_parsePoint(line)));
	if (line[0] == 's' && line[1] == 'p')
		data->objects = ft_olstadd_back(data->objects, ft_olstnew(ft_parseSphere(line)));
	if (line[0] == 't' && line[1] == 'r')
		data->objects = ft_olstadd_back(data->objects, ft_olstnew(ft_parseTriangle(line)));
	return (data);
}

t_parsedData	*ft_parser(int argc, char *argv[])
{
	t_parsedData	*ret;
	int				fd;
	char			*line;
	int				i;

	ret = malloc(sizeof(t_parsedData));
	ret->lights = 0;
	ret->objects = 0;
	if (argc >= 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (1)
		{
			i = get_next_line(fd, &line);
			if (i == 1)
				ret = ft_parseProcessor(line, ret);
			else if (i == -1)
				return (0);
			else if (i == 0)
			{
				ret = ft_parseProcessor(line, ret);
				break;
			}
		}
		close(fd);
	}
	return (ret);
}
