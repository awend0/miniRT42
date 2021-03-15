/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 02:41:39 by hasv              #+#    #+#             */
/*   Updated: 2021/03/15 01:50:03 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

int		ft_exit(t_mlxvars *vars, char *msg)
{
	int		ret;

	ret = 0;
	if (msg)
		printf("Error\n%s\n", msg);
	if (vars)
	{
		if (vars->img.img)
			mlx_destroy_image(vars->mlx, vars->img.img);
		if (vars->win)
		{
			mlx_clear_window(vars->mlx, vars->win);
			mlx_destroy_window(vars->mlx, vars->win);
		}
	}
	ft_free();
	exit(1);
	return (ret);
}

void	ft_fill_image(t_mlxdata *img, t_parsed_data *data)
{
	t_ray		ray;
	t_color		color;
	t_camera	*camera;
	int			x;
	int			y;

	x = -g_width / 2;
	y = -g_height / 2;
	camera = (t_camera*)data->cameras->node;
	while (x < g_width / 2)
	{
		y = -g_height / 2;
		while (y < g_height / 2)
		{
			ray = ft_rotate(x, y, camera);
			color = ft_trace_ray((t_trpar){ray.origin, ray.direction,
				data->objects, data->lights, 1.0, __DBL_MAX__, R_DEPTH});
			ft_putpixel(img, x, y, color);
			y++;
		}
		x++;
	}
}

void	ft_draw(t_mlxvars *vars, int save)
{
	ft_fill_image(&vars->img, vars->data);
	if (save)
		ft_create_bmp(vars);
	if (!save)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
