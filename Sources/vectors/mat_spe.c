/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_spe_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:38 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 18:20:32 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/vectors.h"

t_mat	init_id_mat(int w)
{
	t_mat	mat;
	int		i;

	if (w <= 0)
		return ((t_mat){-1, -1, NULL});
	if (!(mat.mat = ft_memalloc(w * sizeof(double*))))
		return ((t_mat){-1, -1, NULL});
	i = -1;
	while (++i < w)
		if (!(mat.mat[i] = ft_memalloc(w * sizeof(double))))
			return (free_mat_err(&mat, i));
	i = -1;
	while (++i < w)
		mat.mat[i][i] = 1;
	mat.w = w;
	mat.h = w;
	return (mat);
}

t_mat	rot_mat(t_vec3 v, double theta)
{
	t_mat rot;
	double c;
	double mc;
	double s;

	if ((rot = init_mat(3, 3)).w == -1)
		return (rot);
	c = cos(theta);
	mc = 1 - c;
	s = sin(theta);
	rot.mat[0][0] = c + v.x * v.x * mc;
	rot.mat[1][1] = c + v.y * v.y * mc;
	rot.mat[2][2] = c + v.z * v.z * mc;

	rot.mat[0][1] = v.x * v.y * mc - v.z * s;
	rot.mat[1][0] = v.x * v.y * mc + v.z * s;
	
	rot.mat[2][0] = v.x * v.z * mc - v.y * s;
	rot.mat[0][2] = v.x * v.z * mc + v.y * s;
	
	
	rot.mat[1][2] = v.z * v.y * mc - v.x * s;
	rot.mat[2][1] = v.z * v.y * mc + v.x * s;
	
	return (rot);
}

t_mat3	rot_mat3(t_vec3 v, double theta)
{
	t_mat rot;
	double c;
	double mc;
	double sin;

	c = cos(theta);
	mc = 1 - c;
	s = sin(theta);
	rot.mat[0][0] = c + v.x * v.x * mc;
	rot.mat[1][1] = c + v.y * v.y * mc;
	rot.mat[2][2] = c + v.z * v.z * mc;
	rot.mat[0][1] = v.x * v.y * mc - v.z * s;
	rot.mat[1][0] = v.x * v.y * mc + v.z * s;
	rot.mat[2][0] = v.x * v.z * mc - v.y * s;
	rot.mat[0][2] = v.x * v.z * mc + v.y * s;
	rot.mat[1][2] = v.z * v.y * mc - v.x * s;
	rot.mat[2][1] = v.z * v.y * mc + v.x * s;
	return (rot);
}

t_mat4	rot_mat4(t_vec3 v, double theta)
{
	t_mat rot;
	double c;
	double mc;
	double sin;

	rot = init_mat4();
	c = cos(theta);
	mc = 1 - c;
	s = sin(theta);
	rot.mat[0][0] = c + v.x * v.x * mc;
	rot.mat[1][1] = c + v.y * v.y * mc;
	rot.mat[2][2] = c + v.z * v.z * mc;
	rot.mat[0][1] = v.x * v.y * mc - v.z * s;
	rot.mat[1][0] = v.x * v.y * mc + v.z * s;
	rot.mat[2][0] = v.x * v.z * mc - v.y * s;
	rot.mat[0][2] = v.x * v.z * mc + v.y * s;
	rot.mat[1][2] = v.z * v.y * mc - v.x * s;
	rot.mat[2][1] = v.z * v.y * mc + v.x * s;
	return (rot);
}