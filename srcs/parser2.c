/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:40:52 by hasv              #+#    #+#             */
/*   Updated: 2021/03/06 12:55:09 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_light			*ft_parse_pnt(char *line)
{
	char	**words;
	t_light	*ret;

	ret = ft_malloc_save(sizeof(t_light));
	words = ft_split(line, ' ');
	ret->type = POINT;
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
	ret->type = AMBIENT;
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

t_camera		*ft_parse_camera(char *line)
{
	char		**words;
	t_camera	*ret;

	ret = ft_malloc_save(sizeof(t_camera));
	words = ft_split(line, ' ');
	ret->pos = ft_stop(words[1]);
	ret->rotation = ft_vec_norm(ft_stop(words[2]));
	ret->fov = ft_stof(words[3]);
	ret->viewport.width = 2.0 * tan((ret->fov / 2.0) * (M_PI / 180.0));
	ret->viewport.height = ret->viewport.width / (g_width / g_height);
	ret->viewport.d = 1.0;
	return (ret);
}

t_object		*ft_parse_sphere(char *line)
{
	char			**words;
	t_object		*ret;
	t_sp_params		params;

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
