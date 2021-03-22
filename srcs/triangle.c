/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymun <mraymun@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:46:35 by hasv              #+#    #+#             */
/*   Updated: 2021/03/22 02:30:34 by mraymun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_point		ft_get_normal_triangle(void *data, t_point intersection, t_ray ray)
{
	t_triangle	*tr;

	tr = data;
	return (ft_rotate_normal(ray, tr->norm, intersection));
}

int			ft_check(t_triangle *triangle, t_point point, t_point n)
{
	t_point		tmp;

	tmp = ft_vec_cross(ft_vec_s(triangle->b, triangle->a),
		ft_vec_s(point, triangle->a));
	if (ft_vec_dot(n, tmp) < 0)
		return (0);
	tmp = ft_vec_cross(ft_vec_s(triangle->c, triangle->b),
		ft_vec_s(point, triangle->b));
	if (ft_vec_dot(n, tmp) < 0)
		return (0);
	tmp = ft_vec_cross(ft_vec_s(triangle->a, triangle->c),
		ft_vec_s(point, triangle->c));
	if (ft_vec_dot(n, tmp) < 0)
		return (0);
	return (1);
}

t_solutions	ft_intersect_triangle(void *data, t_ray ray)
{
	t_triangle	*tr;
	t_solutions ret;
	t_point		tmp;
	t_point		n;

	tr = data;
	ret = ft_intersect_plane(tr->pl, ray);
	tmp = ft_vec_add(ray.origin, ft_vec_mul(ret.t1, ray.direction));
	n = ft_vec_norm(ft_vec_cross(ft_vec_s(tr->b, tr->a),
		ft_vec_s(tr->c, tr->a)));
	if (ret.t1 < __DBL_MAX__ && ft_check(tr, tmp, n))
		return (ret);
	return ((t_solutions){__DBL_MAX__, __DBL_MAX__});
}

t_object	*ft_create_triangle(t_tr_params params)
{
	t_triangle	*triangle;
	t_object	*obj;

	triangle = ft_malloc_save(sizeof(t_triangle));
	obj = ft_malloc_save(sizeof(t_object));
	triangle->pl = ft_malloc_save(sizeof(t_plane));
	triangle->a = params.a;
	triangle->b = params.b;
	triangle->c = params.c;
	triangle->norm = ft_vec_norm(ft_vec_cross(ft_vec_s(triangle->b,
		triangle->a), ft_vec_s(triangle->c, triangle->a)));
	triangle->pl->p = triangle->a;
	triangle->pl->norm = triangle->norm;
	obj->type = TRIANGLE;
	obj->data = triangle;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	obj->ft_intersect = ft_intersect_triangle;
	obj->ft_get_norm = ft_get_normal_triangle;
	return (obj);
}
