/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:09:10 by hasv              #+#    #+#             */
/*   Updated: 2021/03/06 19:14:17 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

double		g_width;
double		g_height;
t_list		*g_first_cam;
t_color		g_background_color = {0.0, 0.0, 0.0};
t_list		*g_memory = 0;

int		ft_exit(t_mlxvars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	ft_free();
	exit(1);
	return (0);
}

int		ft_expose(t_mlxvars *vars)
{
	printf("a\n");
	ft_draw(vars);
	return (0);
}

int		ft_key_pressed(int keycode, t_mlxvars *vars)
{
	if (keycode == KEYCODE_ESC)
		ft_exit(vars);
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

int		main(int argc, char *argv[])
{
	t_mlxvars		vars;

	vars.data = ft_parser(argc, argv);
	g_first_cam = vars.data->cameras;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx,
		g_width, g_height, "miniRT");
	vars.img.img = mlx_new_image(vars.mlx, g_width, g_height);
	vars.img.addr = mlx_get_data_addr(vars.img.img,
		&vars.img.bbp, &vars.img.line_len, &vars.img.endian);
	mlx_key_hook(vars.win, ft_key_pressed, &vars);
	mlx_expose_hook(vars.win, ft_expose, &vars);
	mlx_hook(vars.win, 33, 0L, ft_exit, &vars);
	ft_draw(&vars);
	mlx_loop(vars.mlx);
}
