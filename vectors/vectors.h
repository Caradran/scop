/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:46 by esuits            #+#    #+#             */
/*   Updated: 2019/04/24 17:56:48 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include "libft.h"
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

typedef struct	s_vec
{
	int		size;
	double	*vec;
}				t_vec;

typedef struct	s_mat
{
	int		w;
	int		h;
	double	**mat;
}				t_mat;

t_vec2			init_v2(double x, double y);
t_vec3			init_v3(double x, double y, double z);
t_vec			init_v(int size);
t_mat			init_mat(int w, int h);

void			free_v(t_vec *a);
void			free_mat(t_mat *a);
t_mat			free_mat_err(t_mat *mat, int i);

t_vec2			mult_v2(t_vec2 a, t_vec2 b);
t_vec3			mult_v3(t_vec3 a, t_vec3 b);
t_mat			mult_mat(t_mat a, t_mat b);
t_vec			mult_v(t_vec a, t_vec b);

t_vec3			mult_mat_v3(t_vec3 a, t_mat b);
t_vec2			mult_mat_v2(t_vec2 a, t_mat b);
t_vec			mult_mat_v(t_vec a, t_mat b);

t_vec2			add_v2(t_vec2 a, t_vec2 b);
t_vec3			add_v3(t_vec3 a, t_vec3 b);
t_mat			add_mat(t_mat a, t_mat b);
t_vec			add_v(t_vec a, t_vec b);

t_vec2			sub_v2(t_vec2 a, t_vec2 b);
t_vec3			sub_v3(t_vec3 a, t_vec3 b);
t_mat			sub_mat(t_mat a, t_mat b);
t_vec			sub_v(t_vec a, t_vec b);

t_vec2			scale_v2(double a, t_vec2 b);
t_vec3			scale_v3(double a, t_vec3 b);

t_vec2			normalize_v2(t_vec2 a);
double			norme_v2(t_vec2 a);
t_vec3			normalize_v3(t_vec3 a);
double			norme_v3(t_vec3 a);

t_vec2			rot_vec2(t_vec2 v, double theta);
t_vec3			rot_vec3(t_vec3 v, double theta, t_vec3 axis);
t_vec3			rot_vec3_x(t_vec3 v, double theta);
t_vec3			rot_vec3_y(t_vec3 v, double theta);
t_vec3			rot_vec3_z(t_vec3 v, double theta);

t_mat			init_id_mat(int w);
t_mat			rot_mat(t_vec3 v, double theta);

void			print_v2(t_vec2 a);
void			print_v3(t_vec3 a);

#endif
