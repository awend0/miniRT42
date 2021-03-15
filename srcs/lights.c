/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 01:53:05 by hasv              #+#    #+#             */
/*   Updated: 2021/03/15 20:25:36 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

void			ft_compute_lighting3(t_covars *vars, t_copar args)
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

double			ft_compute_lighting2(t_covars vars, t_copar args)
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

void			ft_init_compute(t_covars *vars, t_copar args)
{
	vars->t_max = __DBL_MAX__;
	vars->cur = args.lights;
	vars->ret.color = (t_color){0.0, 0.0, 0.0};
	vars->ret.intensity = 0.0;
	vars->tintensity = 0.0;
}

void			ft_sum_intensity(t_covars *vars, double intensity)
{
	vars->ret.intensity += intensity;
	vars->tintensity += intensity;
}

t_color_i		ft_compute_lighting(t_copar args)
{
	t_covars	vars;

	ft_init_compute(&vars, args);
	while (vars.cur)
	{
		if (((t_light*)vars.cur->node)->ltype == AMBIENT)
			ft_sum_intensity(&vars, ((t_light*)vars.cur->node)->intensity);
		else
		{
			ft_compute_lighting3(&vars, args);
			if ((ft_closest((t_clpar){args.p, vars.light, 0.1,
			vars.t_max, args.objects})).obj
			&& ((t_light*)vars.cur->node)->intensity > 0)
			{
				vars.cur = vars.cur->next;
				continue ;
			}
			ft_sum_intensity(&vars, ft_compute_lighting2(vars, args));
		}
		vars.ret.color = ft_color_average(vars.ret.color, ft_color_multiply(
		vars.tintensity, ((t_light*)vars.cur->node)->color));
		vars.tintensity = 0;
		vars.cur = vars.cur->next;
	}
	return (vars.ret);
}
