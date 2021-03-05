/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:08:28 by hasv              #+#    #+#             */
/*   Updated: 2021/03/06 02:31:44 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_point	ft_rotx(t_point vect, float x)
{
	t_point	ret;

	ret.x = vect.x;
	ret.y = vect.y * cos(x) - vect.z * sin(x);
	ret.z = vect.y * sin(x) + vect.z * cos(x);
	return (ret);
}

t_point	ft_roty(t_point vect, float y)
{
	t_point	ret;

	ret.x = vect.x * cos(y) + vect.z * sin(y);
	ret.y = vect.y;
	ret.z = vect.x * -sin(y) + vect.z * cos(y);
	return (ret);
}

t_point	ft_rotz(t_point vect, float z)
{
	t_point	ret;

	ret.x = vect.x * cos(z) - vect.y * sin(z);
	ret.y = vect.x * sin(z) + vect.y * cos(z);
	ret.z = vect.z;
	return (ret);
}

t_point	ft_rotate(t_point vect, t_point rotation)
{
	t_point	ret;

	ret = ft_rotx(vect, rotation.x);
	ret = ft_roty(vect, rotation.y);
	ret = ft_rotz(vect, rotation.z);
	return (ret);
}