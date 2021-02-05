/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:22:07 by hasv              #+#    #+#             */
/*   Updated: 2021/02/05 09:03:47 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern float g_width;
extern float g_height;
extern t_color g_background_color;

t_solutions	ft_intersect_sphere(void *data, t_point origin, t_point dir)
{
	t_solutions ret;
	t_sphere	*sphere;
	t_point		oc;
	float		discriminant;
	float		k[3];

	sphere = data;
	oc = ft_vec_s(origin, sphere->center);
	k[0] = ft_vec_dot(dir, dir);
	k[1] = 2.0 * ft_vec_dot(oc, dir);
	k[2] = ft_vec_dot(oc, oc) - sphere->radius * sphere->radius;
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

t_point		ft_get_normal_sphere(void *data, t_point intersection)
{
	t_sphere	*sphere;
	t_point		ret;

	sphere = data;
	ret = ft_vec_s(intersection, sphere->center);
	ret = ft_vec_multiply(1.0 / ft_vec_length(ret), ret);
	return (ret);
}

t_object	*ft_create_sphere(t_sphereParams params)
{
	t_sphere		*sphere;
	t_object		*obj;

	sphere = malloc(sizeof(t_sphere));
	obj = malloc(sizeof(t_object));
	sphere->center = params.center;
	sphere->radius = params.radius;
	obj->data = sphere;
	obj->e_type = SPHERE;
	obj->ft_intersect = ft_intersect_sphere;
	obj->ft_getNormal = ft_get_normal_sphere;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	return (obj);
}
