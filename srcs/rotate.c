/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:08:28 by hasv              #+#    #+#             */
/*   Updated: 2021/03/12 07:42:48 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_point		ft_multdir(t_point p, t_matrix m)
{
	t_point res;

	res.x = p.x * m.d[0][0] + p.y * m.d[1][0] + p.z * m.d[2][0] + m.d[3][0];
	res.y = p.x * m.d[0][1] + p.y * m.d[1][1] + p.z * m.d[2][1] + m.d[3][1];
	res.z = p.x * m.d[0][2] + p.y * m.d[1][2] + p.z * m.d[2][2] + m.d[3][2];
	return (res);
}

t_matrix	ft_look_at(t_point origin, t_point rotation)
{
	t_matrix	m;
	t_point		random;
	t_point		right;
	t_point		up;

	random = ft_vec_norm((t_point){0, 1, 0});
	right = ft_vec_norm(ft_vec_cross(random, rotation));
	up = ft_vec_norm(ft_vec_cross(rotation, right));
	m.d[0][0] = right.x;
	m.d[0][1] = right.y;
	m.d[0][2] = right.z;
	m.d[1][0] = up.x;
	m.d[1][1] = up.y;
	m.d[1][2] = up.z;
	m.d[2][0] = rotation.x;
	m.d[2][1] = rotation.y;
	m.d[2][2] = rotation.z;
	m.d[3][0] = origin.x;
	m.d[3][1] = origin.y;
	m.d[3][2] = origin.z;
	return (m);
}

t_point		ft_canvas_to_viewport(double x, double y, t_camera *cam)
{
	t_point	ret;
	double	fovk;

	fovk = 2.0 * tan((cam->fov / 2.0) * (M_PI / 180.0));
	ret.x = x * fovk / g_width;
	ret.y = y * fovk / (g_width / g_height) / g_height;
	ret.z = 1;
	return (ret);
}

t_ray		ft_rotate(int x, int y, t_camera *cam)
{
	t_matrix	c2w;
	t_ray		ret;

	c2w = ft_look_at(cam->pos, ft_vec_norm(cam->rotation));
	ret.origin = ft_multdir((t_point){0, 0, 0}, c2w);
	ret.direction = ft_canvas_to_viewport(x, y, cam);
	ret.direction = ft_multdir(ret.direction, c2w);
	ret.direction = ft_vec_norm(ft_vec_s(ret.direction, ret.origin));
	return (ret);
}
