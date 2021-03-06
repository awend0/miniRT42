/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:42:25 by hasv              #+#    #+#             */
/*   Updated: 2021/03/06 12:56:57 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_list		*ft_cylinder_caps(t_object *obj, t_cy_params params)
{
	t_list		*ret;
	t_object	*top_cap;
	t_object	*bottom_cap;

	top_cap = ft_create_disc((t_ds_params){
		params.p,
		ft_vec_mul(-1, params.orient),
		params.color,
		params.diam / 2.0,
		params.reflection,
		params.spec});
	bottom_cap = ft_create_disc((t_ds_params){
		ft_vec_add(params.p, ft_vec_mul(params.height, params.orient)),
		params.orient,
		params.color,
		params.diam / 2.0,
		params.reflection,
		params.spec});
	ret = ft_lnew(obj);
	ret->next = ft_lnew(top_cap);
	((t_list*)ret->next)->next = ft_lnew(bottom_cap);
	return (ret);
}

t_list		*ft_parse_cylinder(char *line)
{
	char		**words;
	t_object	*ret;
	t_cy_params	params;
	int			caps;

	words = ft_split(line, ' ');
	params.p = ft_stop(words[1]);
	params.orient = ft_stop(words[2]);
	params.color = ft_stoc(words[3]);
	params.diam = ft_stof(words[4]);
	params.height = ft_stof(words[5]);
	params.reflection = 0.5;
	params.spec = 500;
	caps = 0;
	if (words[6])
		caps = ft_atoi(words[6]);
	if (words[7])
		params.reflection = ft_stof(words[7]);
	if (words[8])
		params.spec = ft_stof(words[8]);
	ret = ft_create_cylinder(params);
	if (caps)
		return (ft_cylinder_caps(ret, params));
	return (ft_lnew(ret));
}

t_object	*ft_parse_cone(char *line)
{
	char		**words;
	t_object	*ret;
	t_co_params	params;

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

t_object	*ft_parse_tr(char *line)
{
	char		**words;
	t_object	*ret;
	t_tr_params	params;

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

t_object	*ft_parse_plane(char *line)
{
	char		**words;
	t_object	*ret;
	t_pl_params	params;

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