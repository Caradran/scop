/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:46 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 21:31:05 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include "../libft/include/libft.h"
# include <math.h>
# include <stdio.h>

typedef struct	s_vec2
{
	double	x;
	double	y;
}				t_vec2;

typedef struct	s_ivec2
{
	int		x;
	int		y;
}				t_ivec2;

typedef t_vec2	t_size;

typedef t_vec2	t_pos;

typedef t_ivec2	t_isize;

typedef t_vec2	t_ipos;

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_vec4;

typedef struct	s_vec
{
	int		size;
	double	*vec;
}				t_vec;

typedef struct	s_mat3
{
	double mat[3][3];
}				t_mat3;

typedef struct	s_mat4
{
	double mat[4][4];
}				t_mat4;

typedef struct	s_mat
{
	int		w;
	int		h;
	double	**mat;
}				t_mat;


// vec_init.c
t_vec2			init_v2(double x, double y);
t_vec3			init_v3(double x, double y, double z);
t_vec4			init_v4(double x, double y, double z, double w);
t_vec			init_v(int size);

// mat_init.c
t_mat3			init_mat3(void);
t_mat4			init_mat4(void);
t_mat			init_mat(int w, int h);

//vec_free.c
void			free_v(t_vec *a);
void			free_mat(t_mat *a);
t_mat			free_mat_err(t_mat *mat, int i);

// vec_mult.c
t_vec2			mult_vec2(t_vec2 a, t_vec2 b);
t_vec3			mult_vec3(t_vec3 a, t_vec3 b);
t_vec4 			mult_vec4(t_vec4 a, t_vec4 b);
t_vec			mult_vec(t_vec a, t_vec b);

// mat_mult.c
t_mat3			mult_mat3(t_mat3 a, t_mat3 b);
t_mat4			mult_mat4(t_mat4 a, t_mat4 b);
t_mat			mult_mat(t_mat a, t_mat b);

//	vec_mult_mat.c
t_vec2			mult_mat_v2(t_vec2 a, t_mat b);
t_vec3			mult_mat_v3(t_vec3 a, t_mat b);
t_vec4			mult_mat_v4(t_vec4 a, t_mat b);
t_vec3			mult_mat3_v3(t_vec3 a, t_mat3 b);
t_vec4			mult_mat4_v4(t_vec4 a, t_mat4 b);
t_vec			mult_mat_v(t_vec a, t_mat b);


// vec_get_value.c
double			get_value_vec2(t_vec2 a, int b);
double			get_value_vec3(t_vec3 a, int b);
double			get_value_vec4(t_vec4 a, int b);

// vec_add.c
t_vec2			add_v2(t_vec2 a, t_vec2 b);
t_vec3			add_v3(t_vec3 a, t_vec3 b);
t_vec			add_v(t_vec a, t_vec b);

// mat_add.c
t_mat3			add_mat3(t_mat3 a, t_mat3 b);
t_mat4			add_mat4(t_mat4 a, t_mat4 b);
t_mat			add_mat(t_mat a, t_mat b);

// vec_sub.c
t_vec2			sub_v2(t_vec2 a, t_vec2 b);
t_vec3			sub_v3(t_vec3 a, t_vec3 b);
t_vec			sub_v(t_vec a, t_vec b);

// mat_sub.c
t_mat3			sub_mat3(t_mat3 a, t_mat3 b);
t_mat4			sub_mat4(t_mat4 a, t_mat4 b);
t_mat			sub_mat(t_mat a, t_mat b);

// vec_scale.c
t_vec2			scale_v2(double a, t_vec2 b);
t_vec3			scale_v3(double a, t_vec3 b);
t_vec4			scale_v4(double a, t_vec4 b);
t_vec			scale_v(double a, t_vec b);

// mat_scale.c
t_mat3			scale_mat3(double a, t_mat3 b);
t_mat4			scale_mat4(double a, t_mat4 b);
t_mat			scale_mat(double a, t_mat b);

// vec_normalize.c
t_vec2			normalize_v2(t_vec2 a);
t_vec3			normalize_v3(t_vec3 a);
t_vec4			normalize_v4(t_vec4 a);

// vec_norm.c
double			norme_v2(t_vec2 a);
double			norme_v3(t_vec3 a);
double			norme_v4(t_vec4 a);

// vec_dot.c
double	dot_vec2(t_vec2 a, t_vec2 b);
double	dot_vec3(t_vec3 a, t_vec3 b);
double	dot_vec4(t_vec4 a, t_vec4 b);
double	vec_dot(t_vec a, t_vec b);
t_vec3	cross_vec3(t_vec3 a, t_vec3 b);


// vec_print.c
void			print_v2(t_vec2 a);
void			print_v3(t_vec3 a);
void			print_v4(t_vec4 a);

// mat_print.c
void			print_mat3(t_mat3 a);
void			print_mat4(t_mat4 a);
void			print_mat(t_mat a);

// vec_rot.c
t_vec2			rot_vec2(t_vec2 v, double theta);

t_vec3			rot_vec3(t_vec3 v, double theta, t_vec3 axis);
t_vec3			rot_vec3_x(t_vec3 v, double theta);
t_vec3			rot_vec3_y(t_vec3 v, double theta);
t_vec3			rot_vec3_z(t_vec3 v, double theta);

t_vec4			rot_vec4(t_vec4 v, double theta, t_vec3 axis);
t_vec4			rot_vec4_x(t_vec4 v, double theta);
t_vec4			rot_vec4_y(t_vec4 v, double theta);
t_vec4			rot_vec4_z(t_vec4 v, double theta);

t_mat4			translation_mat4(t_vec3 v);
t_mat4			scaling_mat4(t_vec3 v);


//mat_spe.c

t_mat			init_id_mat(int w);
t_mat			rot_mat(t_vec3 v, double theta);
t_mat3			rot_mat3(t_vec3 v, double theta);
t_mat4			rot_mat4(t_vec3 v, double theta);

// mat_to_a.c
double *mat4_to_a(t_mat4 mat);
double *mat3_to_a(t_mat3 mat);


#endif
