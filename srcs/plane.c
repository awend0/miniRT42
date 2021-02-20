/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:30:52 by hasv              #+#    #+#             */
/*   Updated: 2021/02/20 20:12:29 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_solutions	ft_intersect_plane(void *data, t_point origin, t_point dir)
{
	t_plane		*pl;
	t_solutions	ret;
	double		denom;
	double		t;

	ret.t1 = __DBL_MAX__;
	ret.t2 = __DBL_MAX__;
	pl = data;
	denom = ft_vec_dot(pl->norm, dir);
	if (fabs(denom) > 0.001)
	{
		t = ft_vec_dot(ft_vec_s(pl->p, origin), pl->norm) / denom;
		if (t >= 0)
			ret.t1 = t;
	}
	return (ret);
}

t_point		ft_get_normal_plane(void *data, t_point intersection)
{
	(void)intersection;
	return (((t_plane*)data)->norm);
}

t_object	*ft_create_plane(t_planeParams params)
{
	t_plane		*plane;
	t_object	*obj;

	plane = malloc(sizeof(t_plane));
	obj = malloc(sizeof(t_object));
	plane->p = params.p;
	plane->norm = ft_vec_norm(params.norm);
	obj->data = plane;
	obj->e_type = PLANE;
	obj->ft_intersect = ft_intersect_plane;
	obj->ft_getNormal = ft_get_normal_plane;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	return (obj);
}