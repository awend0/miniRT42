/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:21:38 by hasv              #+#    #+#             */
/*   Updated: 2021/03/06 12:55:09 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_solutions	ft_intersect_square(void *data, t_point origin, t_point dir)
{
	t_square	*sq;
	t_solutions	ret;
	double		k[2];
	t_point		d;

	sq = data;
	k[0] = ft_vec_dot(ft_vec_s(origin, sq->p), sq->orient);
	k[1] = ft_vec_dot(dir, sq->orient);
	if (k[1] == 0 || (k[0] < 0 && k[1] < 0) || (k[0] > 0 && k[1] > 0))
		return ((t_solutions){__DBL_MAX__, __DBL_MAX__});
	ret.t1 = -k[0] / k[1];
	d = ft_vec_s(ft_vec_add(ft_vec_mul(ret.t1, dir), origin), sq->p);
	ret.t2 = sq->size / 2;
	if (fabs(d.x) > ret.t2 || fabs(d.y) > ret.t2 || fabs(d.z) > ret.t2)
		return ((t_solutions){__DBL_MAX__, __DBL_MAX__});
	if (ret.t1 > 0)
		return ((t_solutions){ret.t1, __DBL_MAX__});
	return ((t_solutions){__DBL_MAX__, __DBL_MAX__});
}

t_point		ft_get_normal_square(void *data, t_point intersection)
{
	t_square	*sq;

	(void)intersection;
	sq = data;
	return (ft_vec_norm(sq->orient));
}

t_object	*ft_create_square(t_sq_params params)
{
	t_square	*square;
	t_object	*obj;

	square = ft_malloc_save(sizeof(t_square));
	obj = ft_malloc_save(sizeof(t_object));
	square->p = params.p;
	square->orient = params.orient;
	square->size = params.size;
	obj->data = square;
	obj->type = SQUARE;
	obj->ft_intersect = ft_intersect_square;
	obj->ft_get_norm = ft_get_normal_square;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	return (obj);
}
