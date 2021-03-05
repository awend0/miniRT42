/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:09:10 by hasv              #+#    #+#             */
/*   Updated: 2021/03/05 17:07:42 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double		g_width;
double		g_height;
t_color		g_background_color = {0.0, 0.0, 0.0};
t_list		*g_memory = 0;

void	ft_exit(t_mlxvars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	ft_free();
	exit(1);
}

int		ft_key_pressed(int keycode, t_mlxvars *vars)
{
	if (keycode == KEYCODE_ESC)
		ft_exit(vars);
	return (0);
}

void	ft_fill_image(t_mlxdata *img, t_parsed_data *data)
{
	t_point	direction;
	t_color	color;
	int		x;
	int		y;

	x = -g_width / 2;
	y = -g_height / 2;
	while (x < g_width / 2)
	{
		y = -g_height / 2;
		while (y < g_height / 2)
		{
			direction = ft_canvas_to_viewport(x, y, data->camera.viewport);\
			direction = ft_rotate(direction, data->camera.rotation);
			color = ft_trace_ray((t_traceParams){data->camera.pos, direction,
				data->objects, data->lights, 1.0, __DBL_MAX__, R_DEPTH});
			ft_putpixel(img, x, y, color);
			y++;
		}
		x++;
	}
}

int		main(int argc, char *argv[])
{
	t_parsed_data	*data;
	t_mlxvars		vars;

	data = ft_parser(argc, argv);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx,
		g_width, g_height, "miniRT");
	mlx_key_hook(vars.win, ft_key_pressed, &vars);
	vars.img.img = mlx_new_image(vars.mlx, g_width, g_height);
	vars.img.addr = mlx_get_data_addr(vars.img.img,
		&vars.img.bbp, &vars.img.lineLength, &vars.img.endian);
	ft_fill_image(&vars.img, data);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop(vars.mlx);
}
