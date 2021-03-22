/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymun <mraymun@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 01:53:05 by hasv              #+#    #+#             */
/*   Updated: 2021/03/22 01:53:39 by mraymun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;
extern t_color	g_ambient;

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
		args.p, args.ray);
	vars.n_l = ft_vec_dot(normal, vars.light);
	if (vars.n_l > 0)
		ret += ((t_light*)vars.cur->node)->intensity * vars.n_l /
		(ft_vec_length(normal) * ft_vec_length(vars.light));
	if (args.obj->spec != -1)
	{
		vars.ray = ft_reflect_ray(vars.light, normal);
		vars.r_v = ft_vec_dot(vars.ray, args.view);
		if (vars.r_v > 0)
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
	vars->ret = g_ambient;
	vars->intensity = 0;
}

t_color			ft_compute_lighting(t_copar args)
{
	t_covars	vars;

	ft_init_compute(&vars, args);
	while (vars.cur)
	{
		if (((t_light*)vars.cur->node)->ltype == AMBIENT)
			vars.intensity += ((t_light*)vars.cur->node)->intensity;
		else
		{
			ft_compute_lighting3(&vars, args);
			if ((ft_closest((t_clpar){(t_ray){args.p, vars.light}, 0.1,
			vars.t_max, args.objects})).obj
			&& ((t_light*)vars.cur->node)->intensity > 0)
			{
				vars.cur = vars.cur->next;
				continue ;
			}
			vars.intensity += ft_compute_lighting2(vars, args);
		}
		vars.ret = ft_color_add(vars.ret, ft_color_average(args.obj->color,
		ft_color_multiply(vars.intensity, ((t_light*)vars.cur->node)->color)));
		vars.intensity = 0;
		vars.cur = vars.cur->next;
	}
	return (vars.ret);
}
