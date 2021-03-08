/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:41:45 by hasv              #+#    #+#             */
/*   Updated: 2021/03/08 20:06:27 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

int		ft_red_cross(t_mlxvars *vars)
{
	ft_exit(vars, 0);
	return (0);
}

int		ft_expose(t_mlxvars *vars)
{
	ft_draw(vars);
	return (0);
}

int		ft_key_pressed(int keycode, t_mlxvars *vars)
{
	if (keycode == KEYCODE_ESC)
		ft_exit(vars, 0);
	if (keycode == KEYCODE_Q)
	{
		if (vars->data->cameras->next)
		{
			vars->data->cameras = vars->data->cameras->next;
			ft_draw(vars);
		}
		else if (vars->data->cameras != g_first_cam)
		{
			vars->data->cameras = g_first_cam;
			ft_draw(vars);
		}
	}
	return (0);
}
