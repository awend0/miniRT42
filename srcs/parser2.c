/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymun <mraymun@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:40:52 by hasv              #+#    #+#             */
/*   Updated: 2021/03/22 02:18:26 by mraymun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;
extern t_color	g_ambient;

t_light			*ft_parse_pnt(char *line)
{
	char	**words;
	t_light	*ret;

	ret = ft_malloc_save(sizeof(t_light));
	words = ft_split(line, ISSPACE);
	if (!words[1] || !words[2] || !words[3])
		ft_exit(0, "Required parameter missing in point light!");
	if (words[4])
		ret->ltype = DIRECTION;
	else
		ret->ltype = POINT;
	ret->position = ft_stop(words[1]);
	ret->intensity = ft_stof(words[2]);
	if (ret->intensity < 0 || ret->intensity > 1)
		ft_exit(0, "Incorrect light intensity is set.");
	ret->color = ft_stoc(words[3]);
	return (ret);
}

t_light			*ft_parse_amb(char *line)
{
	char	**words;
	t_light	*ret;

	ret = ft_malloc_save(sizeof(t_light));
	words = ft_split(line, ISSPACE);
	if (!words[1] || !words[2])
		ft_exit(0, "Required parameter missing in ambient light!");
	ret->ltype = AMBIENT;
	ret->intensity = ft_stof(words[1]);
	if (ret->intensity < 0.0 || ret->intensity > 1.0)
		ft_exit(0, "Incorrect intensity");
	ret->color = ft_stoc(words[2]);
	if (g_ambient.r != -1)
		ft_exit(0, "Multiple ambient lights are set.");
	g_ambient = ft_color_multiply(ret->intensity, ret->color);
	return (ret);
}

void			ft_parse_res(char *line)
{
	char	**words;

	words = ft_split(line, ISSPACE);
	if (!words[1] || !words[2])
		ft_exit(0, "Required parameter missing in resolution!");
	if (g_width != 0 || g_height != 0)
		ft_exit(0, "Multiple resolutions are set.");
	g_width = (double)ft_stof(words[1]);
	g_height = (double)ft_stof(words[2]);
	if (g_width <= 0 || g_height <= 0)
		ft_exit(0, "Wrong resolution is set.");
}

t_camera		*ft_parse_camera(char *line)
{
	char		**words;
	t_camera	*ret;

	ret = ft_malloc_save(sizeof(t_camera));
	words = ft_split(line, ISSPACE);
	if (!words[1] || !words[2] || !words[3])
		ft_exit(0, "Required parameter missing in camera!");
	ret->pos = ft_stop(words[1]);
	ret->rotation = ft_stop(words[2]);
	if (ret->rotation.y != 0 && ret->rotation.x == 0 && ret->rotation.z == 0)
		ret->rotation.z = 0.001;
	ret->fov = ft_stof(words[3]);
	if (ret->fov > 180 || ret->fov < 0)
		ft_exit(0, "Incorrect camera FOV.");
	if (ret->fov == 180)
		ret->fov = 179;
	ret->save_pos = ret->pos;
	ret->save_rotation = ret->rotation;
	return (ret);
}

t_object		*ft_parse_sphere(char *line)
{
	char			**words;
	t_object		*ret;
	t_sp_params		params;

	words = ft_split(line, ISSPACE);
	if (!words[1] || !words[2] || !words[3])
		ft_exit(0, "Required parameter missing in sphere!");
	params.center = ft_stop(words[1]);
	params.radius = ft_stof(words[2]);
	params.color = ft_stoc(words[3]);
	params.reflection = 0.1;
	params.spec = 100;
	if (words[4])
		params.reflection = ft_stof(words[4]);
	if (words[4] && words[5])
		params.spec = ft_stof(words[5]);
	ret = ft_create_sphere(params);
	return (ret);
}
