/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:00:17 by hasv              #+#    #+#             */
/*   Updated: 2021/02/05 04:20:42 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern float g_width;
extern float g_height;
extern t_color g_backgroundColor;

t_point		ft_reflectRay(t_point R, t_point N)
{
	return (ft_vecSubtract(ft_vecMultiply(2.0 * ft_vecDot(R, N), N), R));
}

t_point		ft_canvasToViewport(float x, float y, t_viewport viewport)
{
	t_point	ret;
	ret.x = x * viewport.width / g_width;
	ret.y = y * viewport.height / g_height;
	ret.z = viewport.d;
	return (ret);
}

t_closest   ft_closestInter(t_closestParams params)
{
	t_closest		ret;
	t_solutions 	solutions;
	t_objectsList	*cur;

	ret.t = __FLT_MAX__;
	ret.object = 0;
	cur = params.objects;
	while (cur)
	{
		solutions = cur->obj->ft_intersect(cur->obj->data, params.origin, params.direction);
		if (solutions.t1 < ret.t && params.t_min < solutions.t1 && solutions.t1 < params.t_max)
		{
			ret.t = solutions.t1;
			ret.object = cur->obj;
		}
		if (solutions.t2 < ret.t && params.t_min < solutions.t2 && solutions.t2 < params.t_max)
		{
			ret.t = solutions.t2;
			ret.object = cur->obj;
		}
		cur = cur->next;
	}
	return (ret);
}

float		ft_computeLighting(t_computeParams args)
{
	t_point			light;
	t_point			R;
	t_lightsList	*cur;
	t_closest		blocker;
	float			intensity;
	float			normalDotLight;
	float			RDotView;
	float			t_max;

	intensity = 0.0;
	t_max = __FLT_MAX__;
	cur = args.lights;
	while (cur)
	{
		if (cur->light->e_type == AMBIENT)
			intensity += cur->light->intensity;
		else
		{
			if (cur->light->e_type == POINT)
			{
				light = ft_vecSubtract(cur->light->position, args.P);
				t_max = 1.0;
			}
			else if (cur->light->e_type == DIRECTION)
				light = cur->light->position;
			blocker = ft_closestInter((t_closestParams){args.P, light, 0.1, t_max, args.objects});
			if (blocker.object)
			{
				cur = cur->next;
				continue ;
			}
			normalDotLight = ft_vecDot(args.obj->ft_getNormal(args.obj->data, args.P), light);
			if (normalDotLight > 0.0)
				intensity += cur->light->intensity * normalDotLight /
				(ft_vecLength(args.obj->ft_getNormal(args.obj->data, args.P)) * ft_vecLength(light));
			if (args.obj->spec != -1)
			{
				R = ft_reflectRay(light, args.obj->ft_getNormal(args.obj->data, args.P));
				RDotView = ft_vecDot(R, args.view);
				if (RDotView > 0.0)
					intensity += cur->light->intensity * powf(RDotView /
					(ft_vecLength(R) * ft_vecLength(args.view)), args.obj->spec);
			}
		}
		cur = cur->next;
	}
	return (intensity);
}

t_color     ft_traceRay(t_traceParams args)
{
	t_closest		closest;
	t_point			reRay;
	t_color			colors[2];
	float			intensity;


	closest = ft_closestInter((t_closestParams){args.origin, args.direction,
						args.t_min, args.t_max, args.objects});
	if (!closest.object)
		return (g_backgroundColor);
	closest.inter = ft_vecAdd(args.origin, ft_vecMultiply(closest.t, args.direction));
	intensity = ft_computeLighting((t_computeParams){closest.inter, ft_vecMultiply(-1, args.direction), closest.object
													,args.objects, args.lights});
	colors[0] = ft_colorMultiply(intensity, closest.object->color);
	if (closest.object->refl <= 0 || args.recDepth <= 0)
		return (colors[0]);
	reRay = ft_reflectRay(ft_vecMultiply(-1, args.direction),
	closest.object->ft_getNormal(closest.object->data, closest.inter));
	colors[1] = ft_traceRay((t_traceParams){closest.inter, reRay, args.objects,
						args.lights, 0.1, __FLT_MAX__,  args.recDepth -  1});
	return (ft_colorAdd(ft_colorMultiply(1.0 - closest.object->refl, colors[0]),
						ft_colorMultiply(closest.object->refl, colors[1])));
}