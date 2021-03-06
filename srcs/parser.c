/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:18:53 by hasv              #+#    #+#             */
/*   Updated: 2021/03/06 12:55:09 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_object		*ft_parse_disc(char *line)
{
	char			**words;
	t_object		*ret;
	t_ds_params		params;

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

t_object		*ft_parse_square(char *line)
{
	char			**words;
	t_object		*ret;
	t_sq_params		params;

	words = ft_split(line, ' ');
	params.p = ft_stop(words[1]);
	params.orient = ft_stop(words[2]);
	params.size = ft_stof(words[3]);
	params.color = ft_stoc(words[4]);
	params.reflection = 0.5;
	params.spec = 500;
	if (words[5])
		params.reflection = ft_stof(words[5]);
	if (words[6])
		params.spec = ft_stof(words[6]);
	ret = ft_create_square(params);
	return (ret);
}

t_list			*ft_parse_cube2(t_cu_params params)
{
	t_list		*ret;
	int			i;

	ret = 0;
	i = 0;
	while (i < 6)
	{
		ret = ft_ladd(ret, ft_lnew(ft_create_square((t_sq_params){
		(ft_vec_add(params.p, ft_vec_mul(params.size / 2, params.normals[i]))),
		params.normals[i],
		params.size,
		params.color,
		params.reflection,
		params.spec})));
		i++;
	}
	return (ret);
}

t_list			*ft_parse_cube(char *line)
{
	char			**words;
	t_cu_params		params;

	words = ft_split(line, ' ');
	params.p = ft_stop(words[1]);
	params.size = ft_stof(words[2]);
	params.color = ft_stoc(words[3]);
	params.reflection = 0.5;
	params.spec = 500;
	if (words[4])
		params.reflection = ft_stof(words[4]);
	if (words[5])
		params.spec = ft_stof(words[5]);
	params.normals[0] = (t_point){0, 1, 0};
	params.normals[1] = (t_point){0, -1, 0};
	params.normals[2] = (t_point){1, 0, 0};
	params.normals[3] = (t_point){-1, 0, 0};
	params.normals[4] = (t_point){0, 0, 1};
	params.normals[5] = (t_point){0, 0, -1};
	return (ft_parse_cube2(params));
}

t_parsed_data	*ft_parser(int argc, char *argv[])
{
	t_parsed_data	*ret;
	int				fd;
	char			*line;
	int				i;

	ret = ft_init_pd();
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
				break ;
			}
		}
		close(fd);
	}
	return (ret);
}
