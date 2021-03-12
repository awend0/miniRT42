/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:00:17 by hasv              #+#    #+#             */
/*   Updated: 2021/03/12 07:21:42 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_closest	ft_closest_inter(t_clpar params)
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

void		ft_compute_lighting3(t_covars *vars, t_copar args)
{
	if (((t_light*)vars->cur->node)->ltype == POINT)
	{
		vars->light = ft_vec_s(((t_light*)vars->cur->node)->position,
		args.p);
		vars->t_max = 1.0;
	}
	else if (((t_light*)vars->cur->node)->ltype == DIRECTION)
		vars->light = ((t_light*)vars->cur->node)->position;
}

double		ft_compute_lighting2(t_covars vars, t_copar args)
{
	double	ret;
	t_point	normal;

	ret = 0;
	normal = args.obj->ft_get_norm(args.obj->data,
		args.p);
	vars.n_l = ft_vec_dot(normal, vars.light);
	if (vars.n_l > 0.0)
		ret += ((t_light*)vars.cur->node)->intensity * vars.n_l /
		(ft_vec_length(normal) * ft_vec_length(vars.light));
	if (args.obj->spec != -1)
	{
		vars.ray = ft_reflect_ray(vars.light, normal);
		vars.r_v = ft_vec_dot(vars.ray, args.view);
		if (vars.r_v > 0.0)
			ret += ((t_light*)vars.cur->node)->intensity * powf(vars.r_v /
			(ft_vec_length(vars.ray) *
			ft_vec_length(args.view)), args.obj->spec);
	}
	return (ret);
}

double		ft_compute_lighting(t_copar args)
{
	t_covars vars;

	vars.intensity = 0.0;
	vars.t_max = __DBL_MAX__;
	vars.cur = args.lights;
	while (vars.cur)
	{
		if (((t_light*)vars.cur->node)->ltype == AMBIENT)
			vars.intensity += ((t_light*)vars.cur->node)->intensity;
		else
		{
			ft_compute_lighting3(&vars, args);
			if ((ft_closest_inter((t_clpar)
			{args.p, vars.light, 0.1, vars.t_max, args.objects})).obj)
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

t_color		ft_trace_ray(t_trpar args)
{
	t_closest		closest;
	t_point			re_ray;
	t_color			colors[2];
	double			intensity;

	closest = ft_closest_inter((t_clpar){args.origin, args.direction,
						args.t_min, args.t_max, args.objects});
	if (!closest.obj)
		return (g_background_color);
	closest.inter = ft_vec_add(args.origin,
		ft_vec_mul(closest.t, args.direction));
	intensity = ft_compute_lighting((t_copar){closest.inter, ft_vec_mul(-1,
		args.direction), closest.obj, args.objects, args.lights});
	colors[0] = ft_color_multiply(intensity, closest.obj->color);
	if (closest.obj->refl <= 0 || args.r_depth <= 0)
		return (colors[0]);
	re_ray = ft_reflect_ray(ft_vec_mul(-1, args.direction),
	closest.obj->ft_get_norm(closest.obj->data, closest.inter));
	colors[1] = ft_trace_ray((t_trpar){closest.inter, re_ray,
		args.objects, args.lights, 0.1, __DBL_MAX__, args.r_depth - 1});
	return (ft_color_add(ft_color_multiply(1.0 - closest.obj->refl, colors[0]),
						ft_color_multiply(closest.obj->refl, colors[1])));
}
