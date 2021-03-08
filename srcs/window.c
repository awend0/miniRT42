/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 02:41:39 by hasv              #+#    #+#             */
/*   Updated: 2021/03/08 20:07:06 by hasv             ###   ########.fr       */
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
	{
		ret += write(1, "Error\n", 6);
		ret += write(1, msg, ft_strlen(msg));
		ret += write(1, "\n", 1);
	}
	if (vars)
	{
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
	}
	ft_free();
	exit(1);
	return (ret);
}

t_point	ft_canvas_to_viewport(double x, double y, t_viewport viewport)
{
	t_point	ret;

	ret.x = x * viewport.width / g_width;
	ret.y = y * viewport.height / g_height;
	ret.z = viewport.d;
	return (ret);
}

void	ft_fill_image(t_mlxdata *img, t_parsed_data *data)
{
	t_point		direction;
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
			direction = ft_canvas_to_viewport(x, y, camera->viewport);\
			direction = ft_rotate(direction, camera->rotation);
			color = ft_trace_ray((t_trpar){camera->pos, direction,
				data->objects, data->lights, 1.0, __DBL_MAX__, R_DEPTH});
			ft_putpixel(img, x, y, color);
			y++;
		}
		x++;
	}
}

void	ft_draw(t_mlxvars *vars)
{
	ft_fill_image(&vars->img, vars->data);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
