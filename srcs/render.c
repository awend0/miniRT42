/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:00:17 by hasv              #+#    #+#             */
/*   Updated: 2021/02/28 09:56:50 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern double	g_width;
extern double	g_height;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_point		ft_reflect_ray(t_point r, t_point n)
{
	return (ft_vec_s(ft_vec_multiply(2.0 * ft_vec_dot(r, n), n), r));
}

t_point		ft_canvas_to_viewport(double x, double y, t_viewport viewport)
{
	t_point	ret;

	ret.x = x * viewport.width / g_width;
	ret.y = y * viewport.height / g_height;
	ret.z = viewport.d;
	return (ret);
}

t_closest	ft_closest_inter(t_closestParams params)
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

double		ft_compute_lighting(t_computeParams args)
{
	t_point			light;
	t_point			ray;
	t_list			*cur;
	t_closest		blocker;
	double			intensity;
	double			n_l;
	double			r_v;
	double			t_max;

	intensity = 0.0;
	t_max = __DBL_MAX__;
	cur = args.lights;
	while (cur)
	{
		if (((t_light*)cur->node)->e_type == AMBIENT)
			intensity += ((t_light*)cur->node)->intensity;
		else
		{
			if (((t_light*)cur->node)->e_type == POINT)
			{
				light = ft_vec_s(((t_light*)cur->node)->position, args.P);
				t_max = 1.0;
			}
			else if (((t_light*)cur->node)->e_type == DIRECTION)
				light = ((t_light*)cur->node)->position;
			blocker = ft_closest_inter((t_closestParams)
			{args.P, light, 0.1, t_max, args.objects});
			if (blocker.obj)
			{
				cur = cur->next;
				continue ;
			}
			n_l = ft_vec_dot(args.obj->ft_getNormal
			(args.obj->data, args.P), light);
			if (n_l > 0.0)
				intensity += ((t_light*)cur->node)->intensity * n_l /
				(ft_vec_length(args.obj->ft_getNormal(args.obj->data, args.P)) * ft_vec_length(light));
			if (args.obj->spec != -1)
			{
				ray = ft_reflect_ray(light, args.obj->ft_getNormal(args.obj->data, args.P));
				r_v = ft_vec_dot(ray, args.view);
				if (r_v > 0.0)
					intensity += ((t_light*)cur->node)->intensity * powf(r_v /
					(ft_vec_length(ray) * ft_vec_length(args.view)), args.obj->spec);
			}
		}
		cur = cur->next;
	}
	return (intensity);
}

t_color		ft_trace_ray(t_traceParams args)
{
	t_closest		closest;
	t_point			re_ray;
	t_color			colors[2];
	double			intensity;

	closest = ft_closest_inter((t_closestParams){args.origin, args.direction,
						args.t_min, args.t_max, args.objects});
	if (!closest.obj)
		return (g_background_color);
	closest.inter = ft_vec_add(args.origin, ft_vec_multiply(closest.t, args.direction));
	intensity = ft_compute_lighting((t_computeParams){closest.inter, ft_vec_multiply(-1, args.direction), closest.obj
													, args.objects, args.lights});
	colors[0] = ft_color_multiply(intensity, closest.obj->color);
	if (closest.obj->refl <= 0 || args.recDepth <= 0)
		return (colors[0]);
	re_ray = ft_reflect_ray(ft_vec_multiply(-1, args.direction),
	closest.obj->ft_getNormal(closest.obj->data, closest.inter));
	colors[1] = ft_trace_ray((t_traceParams){closest.inter, re_ray, args.objects,
						args.lights, 0.1, __DBL_MAX__,  args.recDepth - 1});
	return (ft_color_add(ft_color_multiply(1.0 - closest.obj->refl, colors[0]),
						ft_color_multiply(closest.obj->refl, colors[1])));
}
