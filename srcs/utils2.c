/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymun <mraymun@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:15:42 by hasv              #+#    #+#             */
/*   Updated: 2021/03/22 00:36:13 by mraymun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_point	ft_vec_mul(double k, t_point a)
{
	t_point ret;

	ret.x = a.x * k;
	ret.y = a.y * k;
	ret.z = a.z * k;
	return (ret);
}

t_point	ft_vec_cross(t_point a, t_point b)
{
	t_point		ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

double	ft_modv(double vx, double vy, double vz)
{
	return (sqrtf(vx * vx + vy * vy + vz * vz));
}

t_point	ft_vec_norm(t_point vec)
{
	t_point	ret;
	double	mod_v;

	mod_v = ft_modv(vec.x, vec.y, vec.z);
	ret.x = vec.x / mod_v;
	ret.y = vec.y / mod_v;
	ret.z = vec.z / mod_v;
	return (ret);
}

t_point	ft_vec_mat(double **mat, t_point vec)
{
	t_point	ret;

	ret = (t_point){0.0, 0.0, 0.0};
	ret.x += vec.x * mat[0][0];
	ret.x += vec.y * mat[0][1];
	ret.x += vec.z * mat[0][2];
	ret.y += vec.x * mat[1][0];
	ret.y += vec.y * mat[1][1];
	ret.y += vec.z * mat[1][2];
	ret.z += vec.x * mat[2][0];
	ret.z += vec.y * mat[2][1];
	ret.z += vec.z * mat[2][2];
	return (ret);
}
