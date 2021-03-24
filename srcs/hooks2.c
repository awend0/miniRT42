#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

void	ft_switch_cam(t_mlxvars *vars)
{
	if (vars->data->cameras->next)
	{
		vars->data->cameras = vars->data->cameras->next;
		ft_draw(vars, 0);
	}
	else if (vars->data->cameras != g_first_cam)
	{
		vars->data->cameras = g_first_cam;
		ft_draw(vars, 0);
	}
}

void	ft_translate_cam(int keycode, t_mlxvars *vars)
{
	t_camera	*cam;
	t_point		translation;

	if (keycode == KEYCODE_W)
		translation = (t_point){0, 0, 0.5};
	if (keycode == KEYCODE_S)
		translation = (t_point){0, 0, -0.5};
	if (keycode == KEYCODE_A)
		translation = (t_point){-0.5, 0, 0};
	if (keycode == KEYCODE_D)
		translation = (t_point){0.5, 0, 0};
	if (keycode == KEYCODE_SHIFT)
		translation = (t_point){0, 0.5, 0};
	if (keycode == KEYCODE_CTRL)
		translation = (t_point){0, -0.5, 0};
	cam = vars->data->cameras->node;
	cam->pos = ft_vec_add(translation, cam->pos);
	ft_draw(vars, 0);
}

void	ft_rotate_cam(int keycode, t_mlxvars *vars)
{
	t_camera	*cam;
	t_point		rotation;

	rotation = (t_point){0, 0, 0};
	cam = vars->data->cameras->node;
	if (keycode == KEYCODE_RSHIFT)
		cam->rotation.z *= -1;
	if (keycode == KEYCODE_UP)
		rotation = (t_point){0, 0.5, 0};
	if (keycode == KEYCODE_DOWN)
		rotation = (t_point){0, -0.5, 0};
	if (keycode == KEYCODE_LEFT)
		rotation = (t_point){-0.5, 0, 0};
	if (keycode == KEYCODE_RIGHT)
		rotation = (t_point){0.5, 0, 0};
	cam->rotation = ft_vec_add(rotation, cam->rotation);
	ft_draw(vars, 0);
}

void	ft_restore_cam(t_mlxvars *vars)
{
	t_camera	*cam;

	cam = vars->data->cameras->node;
	cam->pos = cam->save_pos;
	cam->rotation = cam->save_rotation;
	ft_draw(vars, 0);
}
