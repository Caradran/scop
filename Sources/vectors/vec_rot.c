/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:31 by esuits            #+#    #+#             */
/*   Updated: 2019/04/24 17:56:32 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec3	rot_vec3(t_vec3 v, double theta, t_vec3 axis)
{
	return (mult_mat_v3(v, rot_mat(axis, theta)));
}

t_vec3	rot_vec3_x(t_vec3 v, double theta)
{
	return (mult_mat_v3(v, rot_mat(init_v3(1, 0, 0), theta)));
}

t_vec3	rot_vec3_y(t_vec3 v, double theta)
{
	return (mult_mat_v3(v, rot_mat(init_v3(0, 1, 0), theta)));
}

t_vec3	rot_vec3_z(t_vec3 v, double theta)
{
	return (mult_mat_v3(v, rot_mat(init_v3(0, 0, 1), theta)));
}

t_vec2	rot_vec2(t_vec2 v, double theta)
{
	double tmp;

	tmp = sin(theta) * v.x + cos(theta) * v.y;
	v.x = cos(theta) * v.x - sin(theta) * v.y;
	v.y = tmp;
	return (v);
}
