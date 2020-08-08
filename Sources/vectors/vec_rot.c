/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:31 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 18:19:04 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/vectors.h"

t_vec3	rot_vec3(t_vec3 v, double theta, t_vec3 axis)
{
	return (mult_mat3_v3(v, rot_mat3(axis, theta)));
}

t_vec3	rot_vec3_x(t_vec3 v, double theta)
{
	return (mult_mat3_v3(v, rot_mat3(init_v3(1, 0, 0), theta)));
}

t_vec3	rot_vec3_y(t_vec3 v, double theta)
{
	return (mult_mat3_v3(v, rot_mat3(init_v3(0, 1, 0), theta)));
}

t_vec3	rot_vec3_z(t_vec3 v, double theta)
{
	return (mult_mat3_v3(v, rot_mat3(init_v3(0, 0, 1), theta)));
}

t_vec2	rot_vec2(t_vec2 v, double theta)
{
	double tmp;

	tmp = sin(theta) * v.x + cos(theta) * v.y;
	v.x = cos(theta) * v.x - sin(theta) * v.y;
	v.y = tmp;
	return (v);
}

t_vec4	rot_vec4(t_vec4 v, double theta, t_vec3 axis)
{
	return (mult_mat4_v4(v, rot_mat4(axis, theta)));
}

t_vec4	rot_vec4_x(t_vec4 v, double theta)
{
	return (mult_mat4_v4(v, rot_mat4(init_v3(1, 0, 0), theta)));
}

t_vec4	rot_vec4_y(t_vec4 v, double theta)
{
	return (mult_mat4_v4(v, rot_mat4(init_v3(0, 1, 0), theta)));
}

t_vec4	rot_vec4_z(t_vec4 v, double theta)
{
	return (mult_mat4_v4(v, rot_mat4(init_v3(0, 0, 1), theta)));
}
