/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:10:06 by hasv              #+#    #+#             */
/*   Updated: 2021/03/15 20:34:24 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# define BUFFER_SIZE 1
# define KEYCODE_ESC 65307
# define KEYCODE_Q 113
# define KEYCODE_W 119
# define KEYCODE_A 97
# define KEYCODE_S 115
# define KEYCODE_D 100
# define KEYCODE_SHIFT 65505
# define KEYCODE_CTRL 65507
# define KEYCODE_UP 65362
# define KEYCODE_LEFT 65361
# define KEYCODE_DOWN 65364
# define KEYCODE_RIGHT 65363
# define R_DEPTH 3
# define ISSPACE " \t"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

typedef struct		s_point{
	double			x;
	double			y;
	double			z;
}					t_point;

typedef struct		s_color{
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct		s_color_i{
	t_color			color;
	double			intensity;
}					t_color_i;

typedef struct		s_camera{
	t_point			pos;
	t_point			rotation;
	double			fov;
}					t_camera;

typedef struct		s_mlxdata{
	void			*img;
	char			*addr;
	int				bbp;
	int				line_len;
	int				endian;
	int				offset;
}					t_mlxdata;

typedef struct		s_solutions{
	double			t1;
	double			t2;
}					t_solutions;

typedef struct		s_sphere{
	t_point			center;
	double			radius;
	int				inside;
}					t_sphere;

typedef struct		s_triangle{
	t_point			a;
	t_point			b;
	t_point			c;
	t_point			norm;
	double			d;
}					t_triangle;

typedef struct		s_tr_params{
	t_point			a;
	t_point			b;
	t_point			c;
	t_color			color;
	double			reflection;
	double			spec;
}					t_tr_params;

typedef struct		s_sp_params{
	t_point			center;
	t_color			color;
	double			radius;
	double			reflection;
	double			spec;
}					t_sp_params;

typedef struct		s_pl_params{
	t_point			p;
	t_point			norm;
	t_color			color;
	double			reflection;
	double			spec;
}					t_pl_params;

typedef struct		s_plane{
	t_point			p;
	t_point			norm;
}					t_plane;

typedef struct		s_disc{
	t_point			p;
	t_point			norm;
	t_plane			*pl;
	double			r;
}					t_disc;

typedef struct		s_ds_params{
	t_point			p;
	t_point			norm;
	t_color			color;
	double			r;
	double			reflection;
	double			spec;
}					t_ds_params;

typedef struct		s_cy_params{
	t_point			p;
	t_point			orient;
	double			diam;
	double			height;
	t_color			color;
	double			reflection;
	double			spec;
}					t_cy_params;

typedef struct		s_cylinder{
	t_point			p;
	t_point			orient;
	t_point			bottom;
	double			diam;
	double			height;
}					t_cylinder;

typedef struct		s_co_params{
	t_point			p;
	t_point			orient;
	float			k;
	float			minm;
	float			maxm;
	t_color			color;
	double			reflection;
	double			spec;
}					t_co_params;

typedef struct		s_cone{
	t_point			p;
	t_point			orient;
	float			k;
	float			minm;
	float			maxm;
}					t_cone;

typedef struct		s_square{
	t_point			p;
	t_point			orient;
	double			size;
}					t_square;

typedef struct		s_sq_params{
	t_point			p;
	t_point			orient;
	double			size;
	t_color			color;
	double			reflection;
	double			spec;
}					t_sq_params;

typedef struct		s_cu_params{
	t_point			p;
	double			size;
	t_color			color;
	double			reflection;
	double			spec;
	t_point			normals[6];
}					t_cu_params;

typedef struct		s_py_params{
	t_point			p;
	double			size;
	double			height;
	t_color			color;
	double			reflection;
	double			spec;
}					t_py_params;

typedef struct		s_l_params{
	int				type;
	double			intensity;
	t_point			position;
}					t_l_params;

typedef struct		s_light{
	enum			e_ltype
	{
		AMBIENT,
		POINT,
		DIRECTION
	}				ltype;
	double			intensity;
	t_point			position;
	t_color			color;
}					t_light;

typedef struct		s_object{
	enum			e_type
	{
		SPHERE,
		TRIANGLE,
		PLANE,
		CYLINDER,
		DISC,
		CONE,
		SQUARE
	}				type;
	void			*data;
	t_solutions		(*ft_intersect)(void *data, t_point or, t_point dir);
	t_point			(*ft_get_norm)(void *data, t_point intersection);
	t_color			color;
	double			refl;
	double			spec;
}					t_object;

typedef struct		s_list{
	void			*node;
	void			*next;
}					t_list;

typedef struct		s_parsed_data{
	t_list			*objects;
	t_list			*lights;
	t_list			*cameras;
}					t_parsed_data;

typedef struct		s_clpar{
	t_point			origin;
	t_point			direction;
	double			t_min;
	double			t_max;
	t_list			*objects;
}					t_clpar;

typedef struct		s_closest{
	t_point			inter;
	t_object		*obj;
	double			t;
}					t_closest;

typedef struct		s_trpar{
	t_point			origin;
	t_point			direction;
	t_list			*objects;
	t_list			*lights;
	double			t_min;
	double			t_max;
	int				r_depth;
}					t_trpar;

typedef struct		s_copar{
	t_point			p;
	t_point			view;
	t_object		*obj;
	t_list			*objects;
	t_list			*lights;
}					t_copar;

typedef struct		s_mlxvars{
	void			*mlx;
	void			*win;
	t_mlxdata		img;
	t_parsed_data	*data;
}					t_mlxvars;

typedef struct		s_matrix{
	double			d[4][4];
}					t_matrix;

typedef struct		s_ray
{
	t_point			origin;
	t_point			direction;
}					t_ray;

typedef struct		s_covars{
	t_point			light;
	t_point			ray;
	t_list			*cur;
	t_closest		blocker;
	t_color_i		ret;
	double			intensity;
	double			tintensity;
	double			n_l;
	double			r_v;
	double			t_max;
}					t_covars;

/*
** Utils;
*/
double				ft_vec_dot(t_point a, t_point b);
t_point				ft_vec_s(t_point o, t_point d);
double				ft_vec_length(t_point a);
t_point				ft_vec_mul(double k, t_point a);
t_point				ft_vec_add(t_point a, t_point b);
void				ft_putpixel(t_mlxdata *data, int x, int y, t_color color);
int					ft_create_trgb(int t, int r, int g, int b);
t_color				ft_color_multiply(double a, t_color color);
t_color				ft_color_add(t_color a, t_color b);
char				**ft_split(char *s, char *delimiters);
int					ft_atoi(char *str);
t_point				ft_vec_cross(t_point a, t_point b);
t_point				ft_vec_norm(t_point vec);
double				ft_modv(double vx, double vy, double vz);
t_point				ft_vec_mat(double **mat, t_point vec);
t_solutions			ft_intersect_plane(void *data, t_point origin, t_point dir);
void				*ft_malloc_save(int size);
void				ft_free(void);
t_ray				ft_rotate(int x, int y, t_camera *cam);
void				ft_draw(t_mlxvars *vars, int save);
void				ft_fill_image(t_mlxdata *img, t_parsed_data *data);
t_point				ft_reflect_ray(t_point r, t_point n);
int					ft_exit(t_mlxvars *vars, char *msg);
int					ft_isdigit(char *str);
int					ft_strcmp(char *s1, char *s2);
t_color				ft_color_average(t_color a, t_color b);

/*
** BMP
*/
void				ft_bmp(int argc, char *argv[]);
int					ft_create_bmp(t_mlxvars *vars);

/*
** Hooks
*/
int					ft_key_pressed(int keycode, t_mlxvars *vars);
int					ft_expose(t_mlxvars *vars);
int					ft_red_cross(t_mlxvars *vars);
void				ft_rotate_cam(int keycode, t_mlxvars *vars);
void				ft_translate_cam(int keycode, t_mlxvars *vars);
void				ft_switch_cam(t_mlxvars *vars);

/*
** Render
*/
t_color				ft_trace_ray(t_trpar args);
t_color_i			ft_compute_lighting(t_copar args);
t_closest			ft_closest(t_clpar params);
t_point				ft_canvas_to_viewport(double x,
					double y, t_camera *cam);
t_point				ft_reflect_ray(t_point r, t_point n);

/*
** Parser
*/
int					ft_open_map(char *filename);
t_parsed_data		*ft_parser(int argc, char *argv[]);
t_parsed_data		*ft_parse_processor(char *line, t_parsed_data *data);
t_point				ft_stop(char *line);
t_color				ft_stoc(char *line);
double				ft_stof(char *line);
t_object			*ft_parse_sphere(char *line);
t_camera			*ft_parse_camera(char *line);
void				ft_parse_res(char *line);
t_light				*ft_parse_amb(char *line);
t_light				*ft_parse_pnt(char *line);
t_object			*ft_parse_plane(char *line);
t_object			*ft_parse_tr(char *line);
t_object			*ft_parse_cone(char *line);
t_list				*ft_parse_cylinder(char *line);
t_list				*ft_cylinder_caps(t_object *obj, t_cy_params params);
t_parsed_data		*ft_init_pd();
t_list				*ft_parse_cube(char *line);
t_list				*ft_parse_cube2(t_cu_params params);
t_object			*ft_parse_square(char *line);
t_object			*ft_parse_disc(char *line);
t_list				*ft_parse_pyramid(char *line);

/*
** Constructors
*/
t_object			*ft_create_sphere(t_sp_params params);
t_object			*ft_create_triangle(t_tr_params params);
t_object			*ft_create_plane(t_pl_params params);
t_object			*ft_create_cylinder(t_cy_params params);
t_object			*ft_create_disc(t_ds_params params);
t_object			*ft_create_cone(t_co_params params);
t_object			*ft_create_square(t_sq_params params);

/*
** Lists
*/
t_list				*ft_ladd(t_list *lst, t_list *new);
t_list				*ft_lnew(void *content);

/*
** get_next_line
*/
int					get_next_line(int fd, char **line);
char				*ft_strnew(int size);
char				*ft_strchr(char *s, int c);
void				*ft_memalloc(int size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					ft_strlen(char *str);
#endif
