/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:15:42 by hasv              #+#    #+#             */
/*   Updated: 2021/02/20 20:12:27 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern double g_width;
extern double g_height;
extern t_color g_background_color;

t_solutions	ft_intersect_cylinder(void *data, t_point origin, t_point dir)
{
	t_solutions	ret;
	t_point		x;
	t_cylinder	*cyl;
	double		k[4];
	double		m[2];

	cyl = data;
	x = ft_vec_s(origin, cyl->p);
	k[0] = ft_vec_dot(dir, dir) - powf(ft_vec_dot(dir, cyl->orient), 2);
	k[1] = (ft_vec_dot(dir, x) - ft_vec_dot(dir, cyl->orient) * ft_vec_dot(x, cyl->orient)) * 2.0;
	k[2] = ft_vec_dot(x, x) - powf(ft_vec_dot(x, cyl->orient), 2) - powf(cyl->diam / 2.0, 2);
	k[3] = k[1] * k[1] - 4 * k[0] * k[2];
	if (k[3] < 0.0)
		return ((t_solutions){__DBL_MAX__, __DBL_MAX__});
	ret.t1 = (-k[1] + sqrtf(k[3])) / (2.0 * k[0]);
	ret.t2 = (-k[1] - sqrtf(k[3])) / (2.0 * k[0]);
	m[0] = ft_vec_dot(dir, cyl->orient) * ret.t1 + ft_vec_dot(x, cyl->orient);
	m[1] = ft_vec_dot(dir, cyl->orient) * ret.t2 + ft_vec_dot(x, cyl->orient);
	if (m[0] < 0 || m[0] > cyl->height)
		ret.t1 = __DBL_MAX__;
	if (m[1] < 0 || m[1] > cyl->height)
		ret.t2 = __DBL_MAX__;
	return (ret); 
}

t_point		ft_get_normal_cylinder(void *data, t_point intersection)
{
	t_cylinder	*cyl;
	double		t;
	t_point		pt;

	cyl = data;
	t = ft_vec_dot(ft_vec_s(intersection, cyl->bottom), cyl->orient);
	pt = ft_vec_add(cyl->bottom, ft_vec_multiply(t, cyl->orient));
	return (ft_vec_norm(ft_vec_s(intersection, pt)));
}

t_object	*ft_create_cylinder(t_cylinderParams params)
{
	t_cylinder		*cyl;
	t_object		*obj;

	cyl = malloc(sizeof(t_cylinder));
	obj = malloc(sizeof(t_object));
	cyl->p = params.p;
	cyl->orient = ft_vec_norm(params.orient);
	cyl->diam = params.diam;
	cyl->height = params.height;
	cyl->bottom = ft_vec_add(cyl->p, ft_vec_multiply(cyl->height, cyl->orient));
	obj->data = cyl;
	obj->e_type = CYLINDER;
	obj->ft_intersect = ft_intersect_cylinder;
	obj->ft_getNormal = ft_get_normal_cylinder;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	return (obj);
}
