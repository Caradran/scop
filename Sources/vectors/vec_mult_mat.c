/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mult_mat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:55:39 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 18:19:04 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/vectors.h"



t_vec2	mult_mat_v2(t_vec2 b, t_mat a)
{
	int		i;
	int		j;
	t_vec2 c;

	c = init_v2(0, 0);
	if (a.w != 2 || a.h != 2)
		return ((t_vec2){NAN, NAN});
	while (++j < 2)
	{
		c.x += a.mat[j][0] * get_value_vec2(b, j);
		c.y += a.mat[j][1] * get_value_vec2(b, j);
	}
	return (c);
}

t_vec3	mult_mat_v3(t_vec3 b, t_mat a)
{
	int		i;
	int		j;
	t_vec3 c;

	c = init_v3(0, 0, 0);
	if (a.w != 3 || a.h != 3)
		return ((t_vec3){NAN, NAN, NAN});
	while (++j < 3)
	{
		c.x += a.mat[j][0] * get_value_vec3(b, j);
		c.y += a.mat[j][1] * get_value_vec3(b, j);
		c.z += a.mat[j][2] * get_value_vec3(b, j);
	}
	return (c);
}

t_vec3	mult_mat3_v3(t_vec3 b, t_mat3 a)
{
	int		i;
	int		j;
	t_vec3 c;

	c = init_v3(0, 0, 0);
	while (++j < 3)
	{
		c.x += a.mat[j][0] * get_value_vec3(b, j);
		c.y += a.mat[j][1] * get_value_vec3(b, j);
		c.z += a.mat[j][2] * get_value_vec3(b, j);
	}
	return (c);
}

t_vec4	mult_mat_v4(t_vec4 b, t_mat a)
{
	int		i;
	int		j;
	t_vec4 c;

	c = init_v4(0, 0, 0, 0);
	if (a.w != 4 || a.h != 4)
		return ((t_vec4){NAN, NAN, NAN, NAN});
	while (++j < 4)
	{
		c.x += a.mat[j][0] * get_value_vec4(b, j);
		c.y += a.mat[j][1] * get_value_vec4(b, j);
		c.z += a.mat[j][2] * get_value_vec4(b, j);
		c.w += a.mat[j][3] * get_value_vec4(b, j);
	}
	return (c);
}

t_vec4	mult_mat4_v4(t_vec4 b, t_mat4 a)
{
	int		i;
	int		j;
	t_vec4 c;

	c = init_v4(0, 0, 0, 0);
	while (++j < 4)
	{
		c.x += a.mat[j][0] * get_value_vec4(b, j);
		c.y += a.mat[j][1] * get_value_vec4(b, j);
		c.z += a.mat[j][2] * get_value_vec4(b, j);
		c.w += a.mat[j][3] * get_value_vec4(b, j);
	}
	return (c);
}

t_vec	mult_mat_v(t_vec b, t_mat a)
{
	int		i;
	int		j;
	t_vec	c;

	if ((a.w != b.size) || ((c = init_v(a.h)).size == -1))
		return ((t_vec){-1, NULL});
	i = -1;
	while (++i < a.h)
	{
		j = -1;
		while (++j < a.w)
			c.vec[i] += a.mat[j][i] * b.vec[j];
	}
	return (c);
}
