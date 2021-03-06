/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:00:17 by hasv              #+#    #+#             */
/*   Updated: 2021/03/06 12:24:35 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

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

void		ft_compute_lighting3(t_comp_vars *vars, t_compParams args)
{
	if (((t_light*)vars->cur->node)->e_type == POINT)
	{
		vars->light = ft_vec_s(((t_light*)vars->cur->node)->position,
		args.P);
		vars->t_max = 1.0;
	}
	else if (((t_light*)vars->cur->node)->e_type == DIRECTION)
		vars->light = ((t_light*)vars->cur->node)->position;
}

double		ft_compute_lighting2(t_comp_vars vars, t_compParams args)
{
	double	ret;

	ret = 0;
	vars.n_l = ft_vec_dot(args.obj->ft_getNormal(args.obj->data,
		args.P), vars.light);
	if (vars.n_l > 0.0)
		ret += ((t_light*)vars.cur->node)->intensity * vars.n_l /
		(ft_vec_length(args.obj->ft_getNormal(args.obj->data,
		args.P)) * ft_vec_length(vars.light));
	if (args.obj->spec != -1)
	{
		vars.ray = ft_reflect_ray(vars.light,
		args.obj->ft_getNormal(args.obj->data, args.P));
		vars.r_v = ft_vec_dot(vars.ray, args.view);
		if (vars.r_v > 0.0)
			ret += ((t_light*)vars.cur->node)->intensity * powf(vars.r_v /
			(ft_vec_length(vars.ray) *
			ft_vec_length(args.view)), args.obj->spec);
	}
	return (ret);
}

double		ft_compute_lighting(t_compParams args)
{
	t_comp_vars vars;

	vars.intensity = 0.0;
	vars.t_max = __DBL_MAX__;
	vars.cur = args.lights;
	while (vars.cur)
	{
		if (((t_light*)vars.cur->node)->e_type == AMBIENT)
			vars.intensity += ((t_light*)vars.cur->node)->intensity;
		else
		{
			ft_compute_lighting3(&vars, args);
			if ((ft_closest_inter((t_closestParams)
			{args.P, vars.light, 0.1, vars.t_max, args.objects})).obj)
			{
				vars.cur = vars.cur->next;
				continue ;
			}
			vars.intensity += ft_compute_lighting2(vars, args);
		}
		vars.cur = vars.cur->next;
	}
	return (vars.intensity);
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
	closest.inter = ft_vec_add(args.origin,
		ft_vec_mul(closest.t, args.direction));
	intensity = ft_compute_lighting((t_compParams){closest.inter, ft_vec_mul(-1,
		args.direction), closest.obj, args.objects, args.lights});
	colors[0] = ft_color_multiply(intensity, closest.obj->color);
	if (closest.obj->refl <= 0 || args.recDepth <= 0)
		return (colors[0]);
	re_ray = ft_reflect_ray(ft_vec_mul(-1, args.direction),
	closest.obj->ft_getNormal(closest.obj->data, closest.inter));
	colors[1] = ft_trace_ray((t_traceParams){closest.inter, re_ray,
		args.objects, args.lights, 0.1, __DBL_MAX__, args.recDepth - 1});
	return (ft_color_add(ft_color_multiply(1.0 - closest.obj->refl, colors[0]),
						ft_color_multiply(closest.obj->refl, colors[1])));
}
