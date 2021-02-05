/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:09:10 by hasv              #+#    #+#             */
/*   Updated: 2021/02/05 10:22:37 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float	g_width;
float	g_height;
t_color	g_background_color = {0.0, 0.0, 0.0};

void		ft_draw_canvas(t_mlxdata *img, t_parsedData *data)
{
	t_point		direction;
	t_color		color;
	int			x;
	int			y;

	x = -g_width / 2;
	y = -g_height / 2;
	while (x < g_width / 2)
	{
		y = -g_height / 2;
		while (y < g_height / 2)
		{
			direction = ft_canvas_to_viewport(x, y, data->camera.viewport);
			color = ft_trace_ray((t_traceParams){data->camera.pos, direction,
				data->objects, data->lights, 1.0, __FLT_MAX__, R_DEPTH});
			ft_putpixel(img, x, y, color);
			y++;
		}
		x++;
	}
}

int			main(int argc, char *argv[])
{
	void			*mlx;
	void			*mlx_win;
	t_parsedData	*data;
	t_mlxdata		img;

	data = ft_parser(argc, argv);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx,
		g_width, g_height, "miniRT");
	img.img = mlx_new_image(mlx, g_width, g_height);
	img.addr = mlx_get_data_addr(img.img,
		&img.bbp, &img.lineLength, &img.endian);
	ft_draw_canvas(&img, data);
	printf("Done!\n");
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
