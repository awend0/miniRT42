/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:10:06 by hasv              #+#    #+#             */
/*   Updated: 2021/03/06 02:45:44 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define BUFFER_SIZE 1
# define KEYCODE_ESC 65307
# define KEYCODE_Q 113
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
#ifndef R_DEPTH
# define R_DEPTH 3
#endif

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

typedef struct		s_viewport{
	double			width;
	double			height;
	double			d;
}					t_viewport;

typedef struct		s_camera{
	t_point			pos;
	t_point			rotation;
	t_viewport		viewport;
	double			fov;
}					t_camera;

typedef struct		s_mlxdata{
	void			*img;
	char			*addr;
	int				bbp;
	int				lineLength;
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

typedef struct		s_triangleParams{
	t_point			a;
	t_point			b;
	t_point			c;
	t_color			color;
	double			reflection;
	double			spec;
}					t_triangleParams;

typedef struct		s_sphereParams{
	t_point			center;
	t_color			color;
	double			radius;
	double			reflection;
	double 			spec;
}					t_sphereParams;

typedef struct		s_planeParams{
	t_point			p;
	t_point			norm;
	t_color			color;
	double			reflection;
	double			spec;
}					t_planeParams;

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

typedef struct		s_discParams{
	t_point			p;
	t_point			norm;
	t_color			color;
	double			r;
	double			reflection;
	double			spec;
}					t_discParams;

typedef struct		s_cylinderParams{
	t_point			p;
	t_point			orient;
	double			diam;
	double			height;
	t_color			color;
	double			reflection;
	double			spec;
}					t_cylinderParams;

typedef struct		s_cylinder{
	t_point			p;
	t_point			orient;
	t_point			bottom;
	double			diam;
	double			height;
}					t_cylinder;

typedef struct		s_coneParams{
	t_point			p;
	t_point			orient;
	float			k;
	float			minm;
	float			maxm;
	t_color			color;
	double			reflection;
	double			spec;
}					t_coneParams;

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

typedef struct		s_squareParams{
	t_point			p;
	t_point			orient;
	double			size;
	t_color			color;
	double			reflection;
	double			spec;
}					t_squareParams;

typedef struct		s_lightParams{
	int				type;
	double			intensity;
	t_point			position;
}					t_lightParams;

typedef struct		s_light{
	enum			ltype{
					AMBIENT,
					POINT,
					DIRECTION
	}				e_type;
	double			intensity;
	t_point			position;
	t_color			color;
}					t_light;

typedef struct		s_object{
	enum			type{
					SPHERE,
					TRIANGLE,
					PLANE,
					CYLINDER,
					DISC,
					CONE,
					SQUARE
	}				e_type;
	void			*data;
	t_solutions		(*ft_intersect)(void *data, t_point O, t_point D);
	t_point			(*ft_getNormal)(void *data, t_point intersection);
	t_color			color;
	double			refl;
	double			spec;
}					t_object;

typedef struct		s_list{
	void			*node;
	void			*next;
}					t_list;

typedef struct		s_parsedData{
	t_list			*objects;
	t_list			*lights;
	t_list			*cameras;
}					t_parsed_data;

typedef struct		s_closestParams{
	t_point			origin;
	t_point			direction;
	double			t_min;
	double			t_max;
	t_list			*objects;
}					t_closestParams;

typedef struct		s_closest{
	t_point			inter;
	t_object		*obj;
	double			t;
}					t_closest;

typedef struct		s_traceParams{
	t_point			origin;
	t_point			direction;
	t_list			*objects;
	t_list			*lights;
	double			t_min;
	double			t_max;
	int				recDepth;
}					t_traceParams;

typedef struct		s_computeParams{
	t_point			P;
	t_point			view;
	t_object		*obj;
	t_list			*objects;
	t_list			*lights;
}					t_computeParams;

typedef struct		s_mlxvars{
    void			*mlx;
    void			*win;
	t_mlxdata		img;
	t_parsed_data	*data;
}					t_mlxvars;

typedef struct		s_matrix
{
	double			d[4][4];
}					t_matrix;

typedef struct		s_ray
{
	t_point			origin;
	t_point			direction;
}					t_ray;

/*
** Utils;
*/
double				ft_vec_dot(t_point a, t_point b);
t_point				ft_vec_s(t_point O, t_point D);
double				ft_vec_length(t_point a);
t_point 			ft_vec_multiply(double k, t_point a);
t_point 			ft_vec_add(t_point a, t_point b);
void				ft_putpixel(t_mlxdata *data, int x, int y, t_color color);
int					ft_create_trgb(int t, int r, int g, int b);
t_color				ft_color_multiply(double a, t_color color);
t_color				ft_color_add(t_color a, t_color b);
char				**ft_split(char	const *s, char c);
int					ft_atoi(char *str);
t_point				ft_vec_cross(t_point A, t_point B);
t_point				ft_vec_norm(t_point vec);
double				ft_modv(double vx, double vy, double vz);
t_point				ft_vec_mat(double **mat, t_point vec);
t_solutions			ft_intersect_plane(void *data, t_point origin, t_point dir);
void    			*ft_malloc_save(int size);
void				ft_free(void);
t_point				ft_rotate(t_point dir, t_point rotation);
void				ft_draw(t_mlxvars *vars);
void				ft_fill_image(t_mlxdata *img, t_parsed_data *data);
int					ft_key_pressed(int keycode, t_mlxvars *vars);

/*
** Render
*/
t_color				ft_trace_ray(t_traceParams args);
double				ft_compute_lighting(t_computeParams args);
t_closest			ft_closest_inter(t_closestParams params);
t_point				ft_canvas_to_viewport(double x, double y, t_viewport viewport);
t_point				ft_reflect_ray(t_point R, t_point N);

/*
** Parser
*/
t_parsed_data		*ft_parser(int argc, char *argv[]);

/*
** Constructors
*/
t_object			*ft_create_sphere(t_sphereParams params);
t_object			*ft_create_triangle(t_triangleParams params);
t_object			*ft_create_plane(t_planeParams params);
t_object			*ft_create_cylinder(t_cylinderParams params);
t_object			*ft_create_disc(t_discParams params);
t_object			*ft_create_cone(t_coneParams params);
t_object			*ft_create_square(t_squareParams params);

/*
** Lists
*/
t_list				*ft_lstadd_back(t_list *lst, t_list *new);
t_list				*ft_lstnew(void *content);

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