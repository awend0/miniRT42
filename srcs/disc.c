/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:29:02 by hasv              #+#    #+#             */
/*   Updated: 2021/03/05 15:56:23 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

extern double	g_width;
extern double	g_height;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_solutions	ft_intersect_disc(void *data, t_point origin, t_point dir)
{
	t_solutions	ret;
	t_disc		*disc;

	disc = data;
	ret = ft_intersect_plane((void*)disc->pl, origin, dir);
	if (ret.t1 < __DBL_MAX__ && ft_vec_length(ft_vec_s(ft_vec_add(
		origin, ft_vec_multiply(ret.t1, dir)), disc->p)) <= disc->r)
		return (ret);
	return ((t_solutions){__DBL_MAX__, __DBL_MAX__});
}

t_point		ft_get_normal_disc(void *data, t_point intersection)
{
	(void)intersection;
	return (((t_disc*)data)->norm);
}

t_object	*ft_create_disc(t_discParams params)
{
	t_disc		*disc;
	t_object	*obj;

	disc = ft_malloc_save(sizeof(t_disc));
	disc->pl = ft_malloc_save(sizeof(t_plane));
	obj = ft_malloc_save(sizeof(t_object));
	disc->p = params.p;
	disc->norm = ft_vec_norm(params.norm);
	disc->r = params.r;
	disc->pl->p = params.p;
	disc->pl->norm = ft_vec_norm(params.norm);
	obj->data = disc;
	obj->e_type = DISC;
	obj->ft_intersect = ft_intersect_disc;
	obj->ft_getNormal = ft_get_normal_disc;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	return (obj);
}
