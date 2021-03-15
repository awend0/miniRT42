/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:09:10 by hasv              #+#    #+#             */
/*   Updated: 2021/03/15 20:36:24 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

double		g_width = 0;
double		g_height = 0;
t_list		*g_first_cam;
t_color		g_background_color = {0.0, 0.0, 0.0};
t_list		*g_memory = 0;
int			g_sepia = 0;

void	ft_check_resolution(t_mlxvars *vars)
{
	int		sizex;
	int		sizey;

	if (g_width > 6000 || g_height > 6000)
	{
		printf("Too large resolution. Setting your display's maximum\n");
		mlx_get_screen_size(vars->mlx, &sizex, &sizey);
		g_width = sizex;
		g_height = sizey;
	}
	if (g_width <= 0 || g_height <= 0)
	{
		printf("No resolution is set. Setting default 600 x 600\n");
		g_width = 600;
		g_height = 600;
	}
}

int		main(int argc, char *argv[])
{
	t_mlxvars		vars;

	if (argc == 3)
		!ft_strcmp(argv[2], "--save") ? ft_bmp(argc, argv)
		: ft_exit(0, "Unknown argument");
	else if (argc != 2)
		ft_exit(0, "Usage: ./miniRT <.rt file> [--save].");
	vars.data = ft_parser(argc, argv);
	g_first_cam = vars.data->cameras;
	vars.mlx = mlx_init();
	ft_check_resolution(&vars);
	mlx_do_key_autorepeatoff(vars.mlx);
	vars.win = mlx_new_window(vars.mlx,
		g_width, g_height, "miniRT");
	vars.img.img = mlx_new_image(vars.mlx, g_width, g_height);
	vars.img.addr = mlx_get_data_addr(vars.img.img,
		&vars.img.bbp, &vars.img.line_len, &vars.img.endian);
	mlx_key_hook(vars.win, ft_key_pressed, &vars);
	mlx_expose_hook(vars.win, ft_expose, &vars);
	mlx_hook(vars.win, 33, 0L, ft_red_cross, &vars);
	ft_draw(&vars, 0);
	mlx_loop(vars.mlx);
}
