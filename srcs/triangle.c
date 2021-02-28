/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:46:35 by hasv              #+#    #+#             */
/*   Updated: 2021/02/28 08:37:27 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern double	g_width;
extern double	g_height;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_point		ft_get_normal_triangle(void *data, t_point intersection)
{
	(void)intersection;
	return (((t_triangle*)data)->norm);
}

int			ft_c(t_point v1, t_point v2, t_point norm)
{
	t_point	norm_v1_v2;

	norm_v1_v2 = ft_vec_cross(v2, v1);
	if (ft_vec_dot(norm_v1_v2, norm) < 0.0)
		return (0);
	return (1);
}

t_solutions	ft_intersect_triangle(void *data, t_point or, t_point dir)
{
	t_triangle	*tr;
	t_solutions ret;
	double		k;
	t_point		inter;

	ret.t1 = __DBL_MAX__;
	ret.t2 = __DBL_MAX__;
	tr = data;
	ret.t2 = __DBL_MAX__;
	k = -(tr->norm.x * or.x + tr->norm.y * or.y +
	tr->norm.z * or.z + tr->d) / ft_vec_dot(tr->norm, dir);
	if (k < 0.1 || fabs(ft_vec_dot(tr->norm, dir)) < 0.1)
		return (ret);
	inter.x = or.x + dir.x * k;
	inter.y = or.y + dir.y * k;
	inter.z = or.z + dir.z * k;
	if (ft_c(ft_vec_s(tr->a, tr->b), ft_vec_s(tr->a, inter), tr->norm)
		&& ft_c(ft_vec_s(tr->b, tr->c), ft_vec_s(tr->b, inter), tr->norm)
		&& ft_c(ft_vec_s(tr->c, tr->a), ft_vec_s(tr->c, inter), tr->norm))
	{
		ret.t1 = ft_vec_length(ft_vec_s(inter, or)) / ft_vec_length(dir);
		return (ret);
	}
	return (ret);
}

t_object	*ft_create_triangle(t_triangleParams params)
{
	t_triangle	*triangle;
	t_object	*obj;

	triangle = ft_malloc_save(sizeof(t_triangle));
	obj = ft_malloc_save(sizeof(t_object));
	triangle->a = params.a;
	triangle->b = params.b;
	triangle->c = params.c;
	triangle->norm = ft_vec_norm(ft_vec_cross(
	ft_vec_s(triangle->a, triangle->c), ft_vec_s(triangle->c, triangle->b)));
	triangle->d = -(triangle->a.x * triangle->norm.x
	+ triangle->a.y * triangle->norm.y + triangle->a.z * triangle->norm.z);
	obj->e_type = TRIANGLE;
	obj->data = triangle;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	obj->ft_intersect = ft_intersect_triangle;
	obj->ft_getNormal = ft_get_normal_triangle;
	return (obj);
}
