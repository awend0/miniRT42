/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:22:07 by hasv              #+#    #+#             */
/*   Updated: 2021/02/04 03:25:03 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern float g_width;
extern float g_height;
extern t_color g_backgroundColor;

t_solutions	ft_intersectSphere(void *data, t_point O, t_point D)
{
	t_solutions ret;
	t_sphere	*sphere;
	t_point		oc;
	float		discriminant;
	float		k[3];

	sphere = data;
	oc = ft_vecSubtract(O, sphere->center);
	k[0] = ft_vecDot(D, D);
	k[1] = 2.0 * ft_vecDot(oc, D);
	k[2] = ft_vecDot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = k[1] * k[1] - 4 * k[0] * k[2];
	if (discriminant < 0.0)
	{
		ret.t1 = __FLT_MAX__;
		ret.t2 = __FLT_MAX__;
		return (ret);
	}
	ret.t1 = (-k[1] + sqrtf(discriminant)) / (2.0 * k[0]);
	ret.t2 = (-k[1] - sqrtf(discriminant)) / (2.0 * k[0]);
	return (ret);
}

t_point		ft_getNormalSphere(void *data, t_point intersection)
{
	t_sphere	*sphere;
	t_point		ret;

	sphere = data;
	ret = ft_vecSubtract(intersection, sphere->center);
	ret = ft_vecMultiply(1.0 / ft_vecLength(ret), ret);
	return (ret);
}

t_object	*ft_createSphere(t_sphereParams params)
{
	t_sphere		*sphere;
	t_object		*obj;

	sphere = malloc(sizeof(t_sphere));
	obj = malloc(sizeof(t_object));
	sphere->center = params.center;
	sphere->radius = params.radius;
	obj->data = sphere;
	obj->e_type = SPHERE;
	obj->ft_intersect = ft_intersectSphere;
	obj->ft_getNormal = ft_getNormalSphere;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	return (obj);
}