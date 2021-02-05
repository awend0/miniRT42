/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:10:06 by hasv              #+#    #+#             */
/*   Updated: 2021/02/05 07:50:51 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
#ifndef RECURSION_DEPTH
# define RECURSION_DEPTH 3
#endif

typedef struct		s_point{
	float			x;
	float			y;
	float			z;
}					t_point;

typedef struct		s_color{
	float			r;
	float			g;
	float			b;
}					t_color;

typedef struct		s_viewport{
	float			width;
	float			height;
	float			d;
}					t_viewport;

typedef struct		s_camera{
	t_point			pos;
	t_viewport		viewport;
	float			fov;
	float			**rotation;
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
	float			t1;
	float			t2;
}					t_solutions;

typedef struct		s_sphere{
	t_point			center;
	float			radius;
}					t_sphere;

typedef struct		s_triangle{
	t_point			a;
	t_point			b;
	t_point			c;
	t_point			norm;
	float			d;
}					t_triangle;

typedef struct		s_triangleParams{
	t_point			a;
	t_point			b;
	t_point			c;
	t_color			color;
	float			reflection;
	float			spec;
}					t_triangleParams;

typedef struct		s_sphereParams{
	t_point			center;
	t_color			color;
	float			radius;
	float			reflection;
	float 			spec;
}					t_sphereParams;

typedef struct		s_object{
	enum			type{
					SPHERE,
					TRIANGLE
	}				e_type;
	void			*data;
	t_solutions		(*ft_intersect)(void *data, t_point O, t_point D);
	t_point			(*ft_getNormal)(void *data, t_point intersection);
	t_color			color;
	float			refl;
	float			spec;
}					t_object;

typedef struct		s_lightParams{
	int				type;
	float			intensity;
	t_point			position;
}					t_lightParams;

typedef struct		s_light{
	enum			ltype{
					AMBIENT,
					POINT,
					DIRECTION
	}				e_type;
	float			intensity;
	t_point			position;
	t_color			color;
}					t_light;

typedef struct		s_objectsList{
	t_object		*obj;
	void			*next;
}					t_objectsList;

typedef struct		s_lightsList{
	t_light			*light;
	void			*next;
}					t_lightsList;

typedef struct		s_parsedData{
	t_objectsList	*objects;
	t_lightsList	*lights;
	t_camera		camera;
}					t_parsedData;

typedef struct		s_closestParams{
	t_point			origin;
	t_point			direction;
	float			t_min;
	float			t_max;
	t_objectsList	*objects;
}					t_closestParams;

typedef struct		s_closest{
	t_point			inter;
	t_object		*object;
	float			t;
}					t_closest;

typedef struct		s_traceParams{
	t_point			origin;
	t_point			direction;
	t_objectsList	*objects;
	t_lightsList	*lights;
	float			t_min;
	float			t_max;
	int				recDepth;
}					t_traceParams;

typedef struct		s_computeParams{
	t_point			P;
	t_point			view;
	t_object		*obj;
	t_objectsList	*objects;
	t_lightsList	*lights;
}					t_computeParams;

/*
** Utils;
*/
float				ft_vecDot(t_point a, t_point b);
t_point				ft_vecSubtract(t_point O, t_point D);
float				ft_vecLength(t_point a);
t_point 			ft_vecMultiply(float k, t_point a);
t_point 			ft_vecAdd(t_point a, t_point b);
void				ft_putPixel(t_mlxdata *data, int x, int y, t_color color);
int					ft_createTrgb(int t, int r, int g, int b);
t_color				ft_colorMultiply(float a, t_color color);
t_color				ft_colorAdd(t_color a, t_color b);
char				**ft_split(char	const *s, char c);
int					ft_atoi(char *str);
t_point				ft_vecCross(t_point A, t_point B);
t_point				ft_vecNormalize(t_point vec);
float				ft_modv(float vx, float vy, float vz);
t_point				ft_vecMatrix(float **mat, t_point vec);

/*
** Render
*/
t_color				ft_traceRay(t_traceParams args);
float				ft_computeLighting(t_computeParams args);
t_closest			ft_closestInter(t_closestParams params);
t_point				ft_canvasToViewport(float x, float y, t_viewport viewport);
t_point				ft_reflectRay(t_point R, t_point N);

/*
** Parser
*/
t_parsedData		*ft_parser(int argc, char *argv[]);

/*
** Constructors
*/
t_object			*ft_createSphere(t_sphereParams params);
t_object			*ft_createTriangle(t_triangleParams params);

/*
** Lists
*/
t_lightsList		*ft_lstadd_back(t_lightsList *lst, t_lightsList *new);
t_lightsList		*ft_lstnew(t_light *content);
t_objectsList		*ft_olstadd_back(t_objectsList *lst, t_objectsList *new);
t_objectsList		*ft_olstnew(t_object *content);

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