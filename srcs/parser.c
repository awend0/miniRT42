/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:18:53 by hasv              #+#    #+#             */
/*   Updated: 2021/02/04 03:25:00 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern float 	g_width;
extern float 	g_height;
extern t_color	g_backgroundColor;

t_light			*ft_parsePoint(char *line)
{
	char	**words;
	char	**temp;
	t_light	*ret;

	ret = malloc(sizeof(t_light));
	words = ft_split(line, ' ');
	ret->e_type = POINT;
	temp = ft_split(words[1], ',');
	ret->position = (t_point){(float)ft_atoi(temp[0]), (float)ft_atoi(temp[1]), (float)ft_atoi(temp[2])};
	temp = ft_split(words[2], '.');
	ret->intensity = (float)ft_atoi(temp[0]) + ((float)ft_atoi(temp[1]) / powf(10, ft_strlen(temp[1])));
	temp = ft_split(words[3], ',');
	ret->color = (t_color){(float)ft_atoi(temp[0]), (float)ft_atoi(temp[1]), (float)ft_atoi(temp[2])};
	free(words);
	free(temp);
	return (ret);
}

t_light			*ft_parseA(char *line)
{
	char	**words;
	char	**temp;
	t_light	*ret;

	ret = malloc(sizeof(t_light));
	words = ft_split(line, ' ');
	ret->e_type = AMBIENT;
	temp = ft_split(words[1], '.');
	ret->intensity = (float)ft_atoi(temp[0]) + ((float)ft_atoi(temp[1]) / powf(10, ft_strlen(temp[1])));
	temp = ft_split(words[2], ',');
	ret->color = (t_color){(float)ft_atoi(temp[0]), (float)ft_atoi(temp[1]), (float)ft_atoi(temp[2])};
	free(words);
	free(temp);
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

t_point			ft_parseCam(char *line)
{
	char	**words;
	char	**temp;
	t_point	ret;

	words = ft_split(line, ' ');
	temp = ft_split(words[1], ',');
	ret.x = (float)ft_atoi(temp[0]);
	ret.y = (float)ft_atoi(temp[1]);
	ret.z = (float)ft_atoi(temp[2]);
	free (words);
	free (temp);
	return (ret);
}

t_object		*ft_parseSphere(char *line) // sp 0,0,20 20 255,0,0 0.5 500
{
	char			**words;
	char			**temp;
	t_object		*ret;
	t_sphereParams	params;

	ret = malloc(sizeof(t_sphere));
	words = ft_split(line, ' ');
	temp = ft_split(words[1], ',');
	params.center = (t_point){(float)ft_atoi(temp[0]), (float)ft_atoi(temp[1]), (float)ft_atoi(temp[2])};
	temp = ft_split(words[2], '.');
	params.radius = (float)ft_atoi(temp[0]) + ((float)ft_atoi(temp[1]) / powf(10, ft_strlen(temp[1])));
	temp = ft_split(words[3], ',');
	params.color = (t_color){(float)ft_atoi(temp[0]), (float)ft_atoi(temp[1]), (float)ft_atoi(temp[2])};
	temp = ft_split(words[4], '.');
	params.reflection = (float)ft_atoi(temp[0]) + ((float)ft_atoi(temp[1]) / powf(10, ft_strlen(temp[1])));
	params.spec = (float)ft_atoi(words[5]);
	ret = ft_createSphere(params);
	free (words);
	free (temp);
	return (ret);
}

t_parsedData	*ft_parseProcessor(char *line, t_parsedData *data)
{
	if (line[0] == 'R')
		ft_parseRes(line);
	if (line[0] == 'A')
		data->lights = ft_lstadd_back(data->lights, ft_lstnew(ft_parseA(line)));
	if (line[0] == 'c')
		data->origin = ft_parseCam(line);
	if (line[0] == 'l')
		data->lights = ft_lstadd_back(data->lights, ft_lstnew(ft_parsePoint(line)));
	if (line[0] == 's' && line[1] == 'p')
		data->objects = ft_olstadd_back(data->objects, ft_olstnew(ft_parseSphere(line)));
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
	ret->viewport.d = 1.0;
	ret->viewport.height = 1.0;
	ret->viewport.width = 1.0;
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
