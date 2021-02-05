/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:46:35 by hasv              #+#    #+#             */
/*   Updated: 2021/02/05 06:21:53 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_point		ft_getNormalTriangle(void *data, t_point intersection)
{
	(void)intersection;
	return (((t_triangle*)data)->norm);
}

int				ft_checkInter(t_point v1, t_point v2, t_point norm)
{    
	t_point	norm_v1_v2;

	norm_v1_v2 = ft_vecCross(v2, v1);
    if (ft_vecDot(norm_v1_v2, norm) < 0.0)
        return (0);
    return (1);
}

t_solutions	ft_intersectTriangle(void *data, t_point O, t_point D)
{
	t_triangle	*tr;
	float		dot;
	t_solutions ret;
	float		k;
	t_point		inter;

	ret.t1 = __FLT_MAX__;
	ret.t2 = __FLT_MAX__;
	tr = data;
	dot = ft_vecDot(tr->norm, D);
	ret.t2 = __FLT_MAX__;
	if(fabs(dot) < 0.1)
		return (ret);
	k = - (tr->norm.x * O.x + tr->norm.y * O.y + tr->norm.z * O.z + tr->d)
			 / dot;
	if(k < 0.1)
		return (ret);
	inter.x = O.x + D.x * k;
	inter.y = O.y + D.y * k;
	inter.z = O.z + D.z * k;
	if (ft_checkInter(ft_vecSubtract(tr->a, tr->b), ft_vecSubtract(tr->a, inter), tr->norm)
		&& ft_checkInter(ft_vecSubtract(tr->b, tr->c), ft_vecSubtract(tr->b, inter), tr->norm)
		&& ft_checkInter(ft_vecSubtract(tr->c, tr->a), ft_vecSubtract(tr->c, inter), tr->norm))
	{
		ret.t1 = ft_vecLength(ft_vecSubtract(inter, O)) / ft_vecLength(D);
		return (ret);
	}
	return (ret);
}

t_object	*ft_createTriangle(t_triangleParams params)
{
	t_triangle  *triangle;
	t_object    *obj;

	triangle = malloc(sizeof(t_triangle));
	obj = malloc(sizeof(t_object));
	triangle->a = params.a;
	triangle->b = params.b;
	triangle->c = params.c;
	triangle->norm = ft_vecNormalize(ft_vecCross(ft_vecSubtract(triangle->a, triangle->c), ft_vecSubtract(triangle->c, triangle->b)));
	triangle->d = -(triangle->a.x * triangle->norm.x + triangle->a.y * triangle->norm.y + triangle->a.z * triangle->norm.z);
	obj->e_type = TRIANGLE;
	obj->data = triangle;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	obj->ft_intersect = ft_intersectTriangle;
	obj->ft_getNormal = ft_getNormalTriangle;
	return (obj);
}