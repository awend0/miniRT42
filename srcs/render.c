/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:00:17 by hasv              #+#    #+#             */
/*   Updated: 2021/03/15 20:23:31 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_closest	ft_closest(t_clpar params)
{
	t_closest		ret;
	t_solutions		ir;
	t_list			*cur;

	ret.t = __DBL_MAX__;
	ret.obj = 0;
	cur = params.objects;
	while (cur)
	{
		ir = ((t_object*)cur->node)->ft_intersect(((t_object*)cur->node)->data,
		params.origin, params.direction);
		if (ir.t1 < ret.t && params.t_min < ir.t1 && ir.t1 < params.t_max)
		{
			ret.t = ir.t1;
			ret.obj = ((t_object*)cur->node);
		}
		if (ir.t2 < ret.t && params.t_min < ir.t2 && ir.t2 < params.t_max)
		{
			ret.t = ir.t2;
			ret.obj = ((t_object*)cur->node);
		}
		cur = cur->next;
	}
	return (ret);
}

t_color		ft_trace_ray(t_trpar args)
{
	t_closest		closest;
	t_point			re_ray;
	t_color			colors[2];
	t_color_i		light;

	closest = ft_closest((t_clpar){args.origin, args.direction,
						args.t_min, args.t_max, args.objects});
	if (!closest.obj)
		return (g_background_color);
	closest.inter = ft_vec_add(args.origin,
		ft_vec_mul(closest.t, args.direction));
	light = ft_compute_lighting((t_copar){closest.inter, ft_vec_mul(-1,
		args.direction), closest.obj, args.objects, args.lights});
	colors[0] = ft_color_average(ft_color_multiply(light.intensity,
		closest.obj->color), light.color);
	if (closest.obj->refl <= 0 || args.r_depth <= 0)
		return (colors[0]);
	re_ray = ft_reflect_ray(ft_vec_mul(-1, args.direction),
	closest.obj->ft_get_norm(closest.obj->data, closest.inter));
	colors[1] = ft_trace_ray((t_trpar){closest.inter, re_ray,
		args.objects, args.lights, 0.1, __DBL_MAX__, args.r_depth - 1});
	return (ft_color_add(ft_color_multiply(1.0 - closest.obj->refl, colors[0]),
						ft_color_multiply(closest.obj->refl, colors[1])));
}
