#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

t_solutions	ft_intersect_plane(void *data, t_ray ray)
{
	t_plane		*pl;
	t_solutions	ret;
	double		denom;
	double		t;

	ret.t1 = __DBL_MAX__;
	ret.t2 = __DBL_MAX__;
	pl = data;
	denom = ft_vec_dot(pl->norm, ray.direction);
	if (fabs(denom) > 0)
	{
		t = ft_vec_dot(ft_vec_s(pl->p, ray.origin), pl->norm) / denom;
		if (t >= 0)
			ret.t1 = t;
	}
	return (ret);
}

t_point		ft_get_normal_plane(void *data, t_point intersection, t_ray ray)
{
	t_plane		*pl;

	pl = data;
	(void)intersection;
	return (ft_rotate_normal(ray, pl->norm, intersection));
}

t_object	*ft_create_plane(t_pl_params params)
{
	t_plane		*plane;
	t_object	*obj;

	plane = ft_malloc_save(sizeof(t_plane));
	obj = ft_malloc_save(sizeof(t_object));
	plane->p = params.p;
	plane->norm = ft_vec_norm(params.norm);
	obj->data = plane;
	obj->type = PLANE;
	obj->ft_intersect = ft_intersect_plane;
	obj->ft_get_norm = ft_get_normal_plane;
	obj->color = params.color;
	obj->refl = params.reflection;
	obj->spec = params.spec;
	return (obj);
}
