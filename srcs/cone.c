/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 04:19:35 by hasv              #+#    #+#             */
/*   Updated: 2021/03/06 02:31:44 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_solutions	ft_intersect_cone(void *data, t_point origin, t_point dir)
{
	t_solutions	ret;
	t_point		x;
	t_cone		*cone;
	double		k[4];
	double		m[2];

	cone = data;
	x = ft_vec_s(origin, cone->p);
	k[0] = ft_vec_dot(dir, dir) - (1.0 + cone->k * cone->k) * pow(ft_vec_dot(x, cone->orient), 2.0);
	k[1] = (ft_vec_dot(dir, x) - (1.0 + cone->k * cone->k) * ft_vec_dot(dir, cone->orient) * ft_vec_dot(x, cone->orient)) * 2.0;
	k[2] = ft_vec_dot(x, x) - (1.0 + cone->k * cone->k) * pow(ft_vec_dot(x, cone->orient), 2);
	k[3] = k[1] * k[1] - 4 * k[0] * k[2];
	if (k[3] < 0.0)
		return ((t_solutions){__DBL_MAX__, __DBL_MAX__});
	ret.t1 = (-k[1] + sqrtf(k[3])) / (2.0 * k[0]);
	ret.t2 = (-k[1] - sqrtf(k[3])) / (2.0 * k[0]);
	m[0] = ft_vec_dot(dir, cone->orient) * ret.t1 + ft_vec_dot(x, cone->orient);
	m[1] = ft_vec_dot(dir, cone->orient) * ret.t2 + ft_vec_dot(x, cone->orient);
	if (m[0] < cone->minm || m[0] > cone->maxm)
		ret.t1 = __DBL_MAX__;
	if (m[1] < cone->minm || m[1] > cone->maxm)
		ret.t2 = __DBL_MAX__;
	return (ret); 
}

t_point		ft_get_normal_cone(void *data, t_point i)
{
	t_cone		*cone;
	t_point		a;
	double		d;
	double		dis;

	cone = data;
	dis = ft_vec_length(ft_vec_s(i, cone->p));
	d = dis * sqrt(1.0 + cone->k * cone->k);
	a = ft_vec_add(cone->p, ft_vec_multiply(d, ft_vec_norm(cone->orient)));
	return (ft_vec_norm(ft_vec_s(i, a)));
}

t_object	*ft_create_cone(t_coneParams params)
{
	t_cone		*cone;
	t_object	*obj;

	cone = ft_malloc_save(sizeof(t_cone));
	obj = ft_malloc_save(sizeof(t_object));
	cone->p = params.p;
	cone->orient = params.orient;
	cone->minm = params.minm;
	cone->maxm = params.maxm;
	cone->k = params.k;
	obj->data = cone;
	obj->e_type = CONE;
	obj->ft_intersect = ft_intersect_cone;
	obj->ft_getNormal = ft_get_normal_cone;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	return (obj);
}