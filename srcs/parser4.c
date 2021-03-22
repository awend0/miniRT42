/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymun <mraymun@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:32:47 by hasv              #+#    #+#             */
/*   Updated: 2021/03/22 00:36:09 by mraymun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_list			*ft_parse_pyramid3(t_list *ret, t_py_params params)
{
	t_point	p;
	double	s;

	p = params.p;
	s = params.size;
	ret = ft_ladd(ret, ft_lnew(ft_create_triangle((t_tr_params){
	(t_point){p.x + s / 2, p.y, p.z - s / 2},
	(t_point){p.x + s / 2, p.y, p.z + s / 2},
	(t_point){p.x, p.y + params.height, p.z},
	params.color, params.reflection, params.spec})));
	ret = ft_ladd(ret, ft_lnew(ft_create_triangle((t_tr_params){
	(t_point){p.x - s / 2, p.y, p.z - s / 2},
	(t_point){p.x, p.y + params.height, p.z},
	(t_point){p.x - s / 2, p.y, p.z + s / 2},
	params.color, params.reflection, params.spec})));
	return (ret);
}

t_list			*ft_parse_pyramid2(t_py_params params)
{
	t_list		*ret;
	t_point		p;
	double		s;

	p = params.p;
	s = params.size;
	ret = 0;
	ret = ft_ladd(ret, ft_lnew(ft_create_square((t_sq_params){params.p,
	(t_point){0, -1, 0}, params.size, params.color, params.reflection,
	params.spec})));
	ret = ft_ladd(ret, ft_lnew(ft_create_triangle((t_tr_params){
	(t_point){p.x - s / 2, p.y, p.z - s / 2},
	(t_point){p.x + s / 2, p.y, p.z - s / 2},
	(t_point){p.x, p.y + params.height, p.z},
	params.color, params.reflection, params.spec})));
	ret = ft_ladd(ret, ft_lnew(ft_create_triangle((t_tr_params){
	(t_point){p.x + s / 2, p.y, p.z + s / 2},
	(t_point){p.x - s / 2, p.y, p.z + s / 2},
	(t_point){p.x, p.y + params.height, p.z},
	params.color, params.reflection, params.spec})));
	return (ft_parse_pyramid3(ret, params));
}

t_list			*ft_parse_pyramid(char *line)
{
	char			**words;
	t_py_params		params;

	words = ft_split(line, ISSPACE);
	if (!words[1] || !words[2] || !words[3] || !words[4])
		ft_exit(0, "Required parameter missing in pyramid!");
	params.p = ft_stop(words[1]);
	params.size = ft_stof(words[2]);
	params.height = ft_stof(words[3]);
	params.color = ft_stoc(words[4]);
	params.reflection = 0.1;
	params.spec = 100;
	if (words[5])
		params.reflection = ft_stof(words[5]);
	if (words[5] && words[6])
		params.spec = ft_stof(words[6]);
	return (ft_parse_pyramid2(params));
}
