#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

int		ft_red_cross(t_mlxvars *vars)
{
	ft_exit(vars, 0);
	return (0);
}

int		ft_expose(t_mlxvars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (1);
}

int		ft_key_pressed(int keycode, t_mlxvars *vars)
{
	if (keycode == KEYCODE_ESC)
		ft_exit(vars, 0);
	if (keycode == KEYCODE_Q)
		ft_switch_cam(vars);
	if (keycode == KEYCODE_W || keycode == KEYCODE_A
		|| keycode == KEYCODE_S || keycode == KEYCODE_D
		|| keycode == KEYCODE_SHIFT || keycode == KEYCODE_CTRL)
		ft_translate_cam(keycode, vars);
	if (keycode == KEYCODE_UP || keycode == KEYCODE_LEFT
		|| keycode == KEYCODE_DOWN || keycode == KEYCODE_RIGHT
		|| keycode == KEYCODE_RSHIFT)
		ft_rotate_cam(keycode, vars);
	if (keycode == KEYCODE_E)
		ft_restore_cam(vars);
	return (0);
}
